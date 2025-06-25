import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class DegreeprogramExtractor(DataExtractor):
    """Extract degree programs with their most common department"""
    
    @property
    def table_name(self) -> str:
        return "DEGREE_PROGRAM"
    
    def extract(self, offeredCourses: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract degree programs and find the most common department for each.
        Same logic as original getDegreePrograms function.
        """
        # Get unique study programs
        names = offeredCourses['studyPrg'].drop_duplicates().dropna().tolist()
        
        degreePrograms = []
        for name in names:
            if not name or pd.isna(name):
                continue
            
            # Find most common department (srvClient) for this study program
            program_data = offeredCourses[offeredCourses['studyPrg'] == name]
            department_counts = program_data['srvClient'].value_counts()
            
            if len(department_counts) > 0:
                most_common_dept = department_counts.index[0]
                degreePrograms.append({
                    'DE_NAME': str(name),
                    'DE_DEPARTMENT': str(most_common_dept)
                })
        
        return degreePrograms