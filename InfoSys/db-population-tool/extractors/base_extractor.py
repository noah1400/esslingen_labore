"""
Base extractor class for database population tool.

This module provides the abstract base class that all extractors must inherit from.
By placing it in the extractors folder, we eliminate import path issues and 
create a clean separation of concerns.
"""

from abc import ABC, abstractmethod
from typing import Dict, List, Any

class DataExtractor(ABC):
    """Base class for table data extractors"""
    
    @abstractmethod
    def extract(self, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract data for this table from provided CSV data and dependencies.
        
        Args:
            **kwargs: CSV DataFrames and dependency data passed by name
            
        Returns:
            List of dictionaries representing table records
        """
        pass
    
    @property
    @abstractmethod
    def table_name(self) -> str:
        """Return the database table name this extractor targets"""
        pass
    
    @property
    def dependencies(self) -> List[str]:
        """
        Return list of table names this extractor depends on.
        
        Dependencies are resolved in topological order, ensuring
        foreign key relationships are satisfied.
        
        Returns:
            List of table names (empty list if no dependencies)
        """
        return []