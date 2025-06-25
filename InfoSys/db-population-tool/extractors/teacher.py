import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class TeacherExtractor(DataExtractor):
    """Extract teachers with all their attributes - base table for professors and lecturers"""
    
    @property 
    def table_name(self) -> str:
        return "TEACHER"
    
    def extract(self, offeredCourses: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract teachers from offered courses data.
        Same logic as original getTeachers function.
        """
        # Get relevant columns and remove duplicates
        teachersDF = offeredCourses[[
            'lecNo', 'lec1stn', 'lecName', 'lecDept', 'lecNotes', 'isprof'
        ]].drop_duplicates()
        
        teachers = []
        for index, row in teachersDF.iterrows():
            # Skip rows with null lecNo (primary key must exist)
            if pd.isna(row['lecNo']):
                continue
            
            teacher = {
                'T_ID': int(row['lecNo']),
                'T_NAME': str(row['lec1stn']) if not pd.isna(row['lec1stn']) else None,
                'T_LASTNAME': str(row['lecName']) if not pd.isna(row['lecName']) else None,
                'T_DEPARTMENT': str(row['lecDept']) if not pd.isna(row['lecDept']) else None,
                'T_NOTES': str(row['lecNotes']) if not pd.isna(row['lecNotes']) else None,
                'T_ISPROFESSOR': row['isprof'] == 'WAHR'
            }
            teachers.append(teacher)
        
        return teachers