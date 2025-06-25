import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class ProfessorExtractor(DataExtractor):
    """Extract professors (teachers where isprof = 'WAHR')"""
    
    @property
    def table_name(self) -> str:
        return "PROFESSOR"
    
    @property
    def dependencies(self) -> List[str]:
        return ["TEACHER"]  # Depends on TEACHER table being processed first
    
    def extract(self, offeredCourses: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract professors from teachers with isprof = 'WAHR'.
        Same logic as original getProfessors function.
        """
        # Filter for professors only
        professorsDF = offeredCourses[
            offeredCourses['isprof'] == True
        ][['lecNo', 'lecRoom']].drop_duplicates()
        
        professors = []
        for index, row in professorsDF.iterrows():
            if pd.isna(row['lecNo']):
                continue
            
            professor = {
                'P_ID': int(row['lecNo']),  # References TEACHER.T_ID
                'P_CREDIT_HOUR_ACCOUNT': 0.0,  # Default value as in original
                'P_ROOM': str(row['lecRoom']) if not pd.isna(row['lecRoom']) else None
            }
            professors.append(professor)
        
        # Sort by ID (same as original)
        professors = sorted(professors, key=lambda x: x['P_ID'])
        
        return professors