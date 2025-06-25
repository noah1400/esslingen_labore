#!/usr/bin/env python3
"""
Simple Database Population Tool with Auto-Discovery

This system automatically discovers extractor classes from the 'extractors' folder.
Each extractor file should have a class named like the filename + 'Extractor'.

Example: department.py should contain class DepartmentExtractor

The system handles:
- Automatic dependency ordering (topological sort)
- Foreign key resolution through previously extracted data
- Proper SQL INSERT statement ordering
"""

import pandas as pd
import sys
import os
import importlib
import logging
from typing import Dict, List, Any, Optional, Type
from abc import ABC, abstractmethod
from datetime import datetime
from pathlib import Path

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

class DataExtractor(ABC):
    """Base class for table data extractors"""
    
    @abstractmethod
    def extract(self, **kwargs) -> List[Dict[str, Any]]:
        """Extract data for this table"""
        pass
    
    @property
    @abstractmethod
    def table_name(self) -> str:
        """Return the table name"""
        pass
    
    @property
    def dependencies(self) -> List[str]:
        """Return list of table names this extractor depends on"""
        return []

class DependencyResolver:
    """Handles dependency ordering using topological sort"""
    
    @staticmethod
    def get_extraction_order(extractors: List[DataExtractor]) -> List[DataExtractor]:
        """
        Sort extractors based on dependencies using topological sort.
        Ensures tables are extracted in the correct order for foreign key resolution.
        """
        # Create a mapping of table names to extractors
        extractor_map = {ext.table_name: ext for ext in extractors}
        
        # Build dependency graph
        graph = {}
        in_degree = {}
        
        for extractor in extractors:
            table_name = extractor.table_name
            graph[table_name] = extractor.dependencies.copy()
            in_degree[table_name] = len(extractor.dependencies)
        
        # Topological sort using Kahn's algorithm
        queue = [table for table, degree in in_degree.items() if degree == 0]
        result = []
        
        while queue:
            current = queue.pop(0)
            result.append(extractor_map[current])
            
            # Update in-degrees of dependent tables
            for table_name, deps in graph.items():
                if current in deps:
                    deps.remove(current)
                    in_degree[table_name] -= 1
                    if in_degree[table_name] == 0:
                        queue.append(table_name)
        
        # Check for circular dependencies
        if len(result) != len(extractors):
            remaining = [ext.table_name for ext in extractors if ext not in result]
            raise ValueError(f"Circular dependency detected involving tables: {remaining}")
        
        logger.info(f"Extraction order: {[ext.table_name for ext in result]}")
        return result

class ExtractorDiscovery:
    """Automatically discovers and loads extractor classes with proper module isolation"""
    
    @staticmethod
    def discover_extractors(extractors_folder: str = "extractors") -> List:
        """
        Discover and instantiate all extractor classes from the extractors folder.
        
        Uses the base_extractor module within the extractors folder to avoid
        module identity conflicts and import path issues.
        
        Expected structure:
        extractors/
        ├── base_extractor.py      # Contains DataExtractor base class
        ├── teacher.py             # Contains TeacherExtractor(DataExtractor)
        ├── professor.py           # Contains ProfessorExtractor(DataExtractor)
        └── ...
        """
        extractors = []
        extractors_path = Path(extractors_folder)
        
        if not extractors_path.exists():
            logger.warning(f"Extractors folder '{extractors_folder}' not found")
            return []
        
        # Add extractors folder to Python path for clean imports
        extractors_abs_path = str(extractors_path.absolute())
        if extractors_abs_path not in sys.path:
            sys.path.insert(0, extractors_abs_path)
        
        try:
            # Import the base class from within the extractors folder
            base_extractor_module = importlib.import_module('base_extractor')
            DataExtractor = base_extractor_module.DataExtractor
            
            logger.info(f"✓ Loaded base DataExtractor from {extractors_folder}/base_extractor.py")
            
            # Discover all extractor modules
            for file_path in extractors_path.glob("*.py"):
                if file_path.name.startswith("_") or file_path.name == "base_extractor.py":
                    continue  # Skip __init__.py, private files, and base class
                
                module_name = file_path.stem
                class_name = module_name.capitalize() + "Extractor"
                
                try:
                    # Import the extractor module
                    module = importlib.import_module(module_name)
                    
                    # Reload module to ensure fresh imports (handles module caching issues)
                    importlib.reload(module)
                    
                    # Get the extractor class
                    if hasattr(module, class_name):
                        extractor_class = getattr(module, class_name)
                        
                        # Verify it's a DataExtractor subclass (now with consistent class identity)
                        if issubclass(extractor_class, DataExtractor):
                            extractor = extractor_class()
                            extractors.append(extractor)
                            logger.info(f"✓ Loaded {class_name} from {file_path.name}")
                        else:
                            logger.warning(f"✗ {class_name} in {file_path.name} is not a DataExtractor subclass")
                            logger.debug(f"  Expected parent: {DataExtractor}")
                            logger.debug(f"  Actual parents: {extractor_class.__bases__}")
                    else:
                        logger.warning(f"✗ Class {class_name} not found in {file_path.name}")
                        # List available classes for debugging
                        available_classes = [name for name in dir(module) 
                                           if isinstance(getattr(module, name), type)]
                        logger.debug(f"  Available classes: {available_classes}")
                        
                except Exception as e:
                    logger.error(f"✗ Failed to load {file_path.name}: {str(e)}")
                    logger.debug(f"  Module path: {file_path}")
                    import traceback
                    logger.debug(f"  Traceback: {traceback.format_exc()}")
            
        except ImportError as e:
            logger.error(f"✗ Could not import base_extractor module: {str(e)}")
            logger.error(f"  Ensure {extractors_folder}/base_extractor.py exists")
            return []
        
        finally:
            # Clean up sys.path to avoid side effects
            if extractors_abs_path in sys.path:
                sys.path.remove(extractors_abs_path)
        
        logger.info(f"Successfully discovered {len(extractors)} extractors")
        
        if not extractors:
            logger.warning("No valid extractors found. Check:")
            logger.warning(f"  1. {extractors_folder}/base_extractor.py exists")
            logger.warning(f"  2. Extractor files import: from base_extractor import DataExtractor")
            logger.warning(f"  3. Classes follow naming convention: FilenameExtractor")
            logger.warning(f"  4. Classes inherit from DataExtractor")
        
        return extractors

class SQLGenerator:
    """Generates SQL INSERT statements with proper ordering and escaping"""
    
    @staticmethod
    def escape_sql_value(value: Any) -> str:
        """Safely escape SQL values to prevent injection"""
        if value is None:
            return 'NULL'
        elif isinstance(value, bool):
            return 'TRUE' if value else 'FALSE'
        elif isinstance(value, (int, float)):
            return str(value)
        else:
            # Escape string values
            escaped = str(value).replace("'", "''")
            return f"'{escaped}'"
    
    @staticmethod
    def generate_insert_statement(table_name: str, record: Dict[str, Any], schema_name: str = None) -> str:
        """Generate a single INSERT statement"""
        columns = [f'"{col}"' for col in record.keys()]
        values = [SQLGenerator.escape_sql_value(val) for val in record.values()]
        
        columns_str = ", ".join(columns)
        values_str = ", ".join(values)

        statement_suffix = f'"{table_name}" ({columns_str}) VALUES ({values_str});'
        if schema_name:
            statement = f'INSERT INTO "{schema_name}".{statement_suffix}'
        else:
            statement = f'INSERT INTO {statement_suffix}'
        
        return statement
    
    @staticmethod
    def generate_sql_file(data: Dict[str, List[Dict[str, Any]]], 
                         extraction_order: List[DataExtractor],
                         schema_name: str = None,
                         output_file: str = "generated_inserts.sql") -> List[str]:
        """Generate complete SQL file with proper ordering"""
        statements = []
        
        # Header
        statements.extend([
            f"-- SQL INSERT statements generated on {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}",
            f"-- Generated by Simple Database Population Tool with Auto-Discovery",
            f"-- Tables processed in dependency order",
            ""
        ])
        
        # Generate INSERT statements in dependency order
        total_inserts = 0
        for extractor in extraction_order:
            table_name = extractor.table_name
            records = data.get(table_name, [])
            
            if not records:
                statements.extend([
                    f"-- No data for table {table_name}",
                    ""
                ])
                continue
            
            statements.extend([
                f"-- Insert data for table {table_name}",
                f"-- Records: {len(records)}",
                f"-- Dependencies: {extractor.dependencies if extractor.dependencies else 'None'}"
            ])
            
            for record in records:
                stmt = SQLGenerator.generate_insert_statement(table_name, record, schema_name)
                statements.append(stmt)
                total_inserts += 1
            
            statements.append("")
        
        # Write to file
        with open(output_file, 'w', encoding='utf-8') as f:
            for stmt in statements:
                f.write(stmt + '\n')
        
        logger.info(f"Generated {total_inserts} INSERT statements in dependency order")
        logger.info(f"SQL saved to {output_file}")
        
        return statements

class SimpleDBPopulator:
    """Main class that orchestrates the data extraction and SQL generation"""
    
    def __init__(self, schema_name: str = None, extractors_folder: str = "extractors"):
        self.schema_name = schema_name
        self.extractors_folder = extractors_folder
        self.extractors = []
        self.extraction_order = []
        self.extracted_data = {}
    
    def discover_and_load_extractors(self):
        """Discover extractors and determine processing order"""
        logger.info("Discovering extractor classes...")
        
        # Discover all extractors
        self.extractors = ExtractorDiscovery.discover_extractors(self.extractors_folder)
        
        if not self.extractors:
            raise ValueError(f"No extractors found in '{self.extractors_folder}' folder")
        
        # Determine extraction order based on dependencies
        self.extraction_order = DependencyResolver.get_extraction_order(self.extractors)
        
        logger.info(f"Loaded {len(self.extractors)} extractors")
        return self.extractors
    
    def load_csv_files(self, **file_paths) -> Dict[str, pd.DataFrame]:
        """
        Load CSV files. Pass file paths as keyword arguments.
        
        Example:
            load_csv_files(
                offeredCourses='data/offeredCourses.csv',
                workload='data/workload.csv'
            )
        """
        logger.info("Loading CSV files...")
        
        csv_data = {}
        for name, path in file_paths.items():
            if not Path(path).exists():
                raise FileNotFoundError(f"CSV file not found: {path}")
            
            # Auto-detect delimiter
            with open(path, 'r', encoding='utf-8') as f:
                first_line = f.readline()
                delimiter = ';' if ';' in first_line else ','
            
            df = pd.read_csv(path, delimiter=delimiter, encoding='utf-8')
            csv_data[name] = df
            
            logger.info(f"✓ Loaded {name}: {len(df)} rows, {len(df.columns)} columns")
        
        return csv_data
    
    def extract_all_data(self, csv_data: Dict[str, pd.DataFrame]) -> Dict[str, List[Dict[str, Any]]]:
        """Extract data from all tables in dependency order"""
        logger.info("Extracting data for all tables...")
        
        for extractor in self.extraction_order:
            logger.info(f"Processing {extractor.table_name}...")
            
            try:
                # Prepare parameters for this extractor
                params = csv_data.copy()
                
                # Add previously extracted data for dependencies
                for dep_table in extractor.dependencies:
                    if dep_table in self.extracted_data:
                        # Use lowercase version of table name as parameter
                        param_name = dep_table.lower()
                        params[param_name] = self.extracted_data[dep_table]
                
                # Extract data
                data = extractor.extract(**params)
                self.extracted_data[extractor.table_name] = data
                
                logger.info(f"✓ {extractor.table_name}: {len(data)} records")
                
                # Log dependency resolution
                if extractor.dependencies:
                    logger.info(f"  Dependencies satisfied: {extractor.dependencies}")
                
            except Exception as e:
                logger.error(f"✗ {extractor.table_name}: {str(e)}")
                logger.error(f"  Available parameters: {list(params.keys())}")
                self.extracted_data[extractor.table_name] = []
        
        total_records = sum(len(data) for data in self.extracted_data.values())
        logger.info(f"Extraction complete: {total_records} total records")
        
        return self.extracted_data
    
    def generate_sql(self, output_file: str = "generated_inserts.sql"):
        """Generate SQL INSERT statements in correct dependency order"""
        logger.info("Generating SQL statements...")
        
        statements = SQLGenerator.generate_sql_file(
            data=self.extracted_data,
            extraction_order=self.extraction_order,
            schema_name=self.schema_name,
            output_file=output_file
        )
        
        return statements
    
    def run(self, output_file: str = "generated_inserts.sql", **csv_files):
        """
        Run the complete process
        
        Example:
            populator.run(
                offeredCourses='data/offeredCourses.csv',
                workload='data/workload.csv',
                output_file='my_inserts.sql'
            )
        """
        try:
            # Discover extractors
            self.discover_and_load_extractors()
            
            # Load CSV files
            csv_data = self.load_csv_files(**csv_files)
            
            # Extract data in dependency order
            self.extract_all_data(csv_data)
            
            # Generate SQL in correct order
            self.generate_sql(output_file)
            
            # Print summary
            self.print_summary()
            
            return True
            
        except Exception as e:
            logger.error(f"Process failed: {str(e)}")
            return False
    
    def print_summary(self):
        """Print extraction summary with dependency information"""
        print("\n" + "=" * 70)
        print("EXTRACTION SUMMARY (Dependency Order)")
        print("=" * 70)
        
        total_records = 0
        for extractor in self.extraction_order:
            table_name = extractor.table_name
            records = self.extracted_data.get(table_name, [])
            count = len(records)
            total_records += count
            
            status = "✓ SUCCESS" if count > 0 else "⚠ NO DATA"
            deps = f"Deps: {extractor.dependencies}" if extractor.dependencies else "Independent"
            
            print(f"{table_name:<20} {count:>6} records  {status:<12} {deps}")
        
        print("-" * 70)
        print(f"{'TOTAL':<20} {total_records:>6} records")
        print("=" * 70)
        
        # Foreign key validation summary
        fk_issues = self._validate_foreign_keys()
        if fk_issues:
            print("\n⚠ FOREIGN KEY WARNINGS:")
            for issue in fk_issues:
                print(f"  - {issue}")
    
    def _validate_foreign_keys(self) -> List[str]:
        """Basic validation of foreign key relationships"""
        issues = []
        
        # Check if dependent tables have data when their dependencies have data
        for extractor in self.extraction_order:
            if extractor.dependencies:
                table_count = len(self.extracted_data.get(extractor.table_name, []))
                
                for dep_table in extractor.dependencies:
                    dep_count = len(self.extracted_data.get(dep_table, []))
                    
                    if dep_count > 0 and table_count == 0:
                        issues.append(f"{extractor.table_name} has no data but dependency {dep_table} has {dep_count} records")
        
        return issues
    
def auto_discover_csv_files(data_directory: str) -> Dict[str, str]:
    """
    Auto-discover CSV files in the specified directory.
    
    Returns a dictionary mapping CSV names (without extension) to their full file paths.
    This maintains compatibility with the existing parameter mapping strategy.
    
    Args:
        data_directory: Path to directory containing CSV files
        
    Returns:
        Dict mapping CSV names to file paths (e.g., {'offeredCourses': 'data/offeredCourses.csv'})
        
    Raises:
        FileNotFoundError: If data directory doesn't exist
        ValueError: If no CSV files found in directory
    """
    data_path = Path(data_directory)
    
    if not data_path.exists():
        raise FileNotFoundError(f"Data directory not found: {data_directory}")
    
    if not data_path.is_dir():
        raise ValueError(f"Path is not a directory: {data_directory}")
    
    # Discover all CSV files
    csv_files = {}
    for csv_file in data_path.glob("*.csv"):
        # Use filename without extension as key (matches existing parameter strategy)
        csv_name = csv_file.stem
        csv_files[csv_name] = str(csv_file)
        logger.info(f"✓ Discovered CSV: {csv_name} -> {csv_file}")
    
    if not csv_files:
        raise ValueError(f"No CSV files found in directory: {data_directory}")
    
    logger.info(f"Auto-discovered {len(csv_files)} CSV files: {list(csv_files.keys())}")
    return csv_files

def main():
    """Main entry point with auto-discovery of CSV files from data directory"""
    import argparse
    
    parser = argparse.ArgumentParser(description="Simple Database Population Tool with Auto-Discovery")
    parser.add_argument('--data-dir', default='data',
                       help='Path to directory containing CSV files (default: data)')
    parser.add_argument('--extractors', default='extractors',
                       help='Path to extractors folder (default: extractors)')
    parser.add_argument('--output', default='generated_inserts.sql',
                       help='Output SQL file path')
    parser.add_argument('--schema', default=None,
                       help='Database schema name, if set, SQL will include schema prefix')
    
    args = parser.parse_args()
    
    try:
        # Auto-discover CSV files in the data directory
        csv_files = auto_discover_csv_files(args.data_dir)
        
        # Create and run the populator with discovered files
        populator = SimpleDBPopulator(args.schema, args.extractors)
        success = populator.run(
            output_file=args.output,
            **csv_files  # Unpack discovered CSV files as keyword arguments
        )
        
        if success:
            print(f"\n🎉 SQL generation completed successfully!")
            print(f"📄 Output saved to: {args.output}")
            print(f"📊 Processed CSV files: {list(csv_files.keys())}")
            print(f"\n💡 To add new tables:")
            print(f"   1. Create a new file in '{args.extractors}/' folder")
            print(f"   2. Name it like: mytable.py")
            print(f"   3. Create class: MytableExtractor(DataExtractor)")
            print(f"   4. Re-run this script")
        else:
            print(f"\n❌ SQL generation failed!")
            sys.exit(1)
            
    except (FileNotFoundError, ValueError) as e:
        logger.error(f"Auto-discovery failed: {str(e)}")
        print(f"\n❌ {str(e)}")
        print(f"💡 Ensure your data directory contains CSV files and try again")
        sys.exit(1)
    except Exception as e:
        logger.error(f"Unexpected error: {str(e)}")
        print(f"\n💥 Unexpected error: {str(e)}")
        sys.exit(1)

if __name__ == "__main__":
    main()