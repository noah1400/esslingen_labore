import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class DepartmentExtractor(DataExtractor):
    """Extract departments by combining multiple columns from offered courses"""
    
    @property
    def table_name(self) -> str:
        return "DEPARTMENT"
    
    def extract(self, offeredCourses: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract departments from srvProvider, srvClient, and lecDept columns.
        Same logic as original getDepartments function.
        """
        # Combine all department-related columns
        all_departments = (
            offeredCourses['srvProvider'].tolist() + 
            offeredCourses['srvClient'].tolist() + 
            offeredCourses['lecDept'].tolist()
        )
        
        # Remove duplicates and null values
        departments = pd.Series(all_departments).drop_duplicates().dropna().tolist()
        
        # Filter out empty strings and clean data
        clean_departments = []
        for dept in departments:
            if dept and str(dept).strip():
                clean_departments.append({'D_NAME': str(dept).strip()})
        
        return clean_departments