import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class SubjectExtractor(DataExtractor):
    """Extract subjects with all attributes"""
    
    @property
    def table_name(self) -> str:
        return "SUBJECT"
    
    @property
    def dependencies(self) -> List[str]:
        return ["DEGREE_PROGRAM"]  # Foreign key reference to degree programs
    
    def extract(self, offeredCourses: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract subjects with numeric conversion for hours.
        Same logic as original getSubjects function.
        """
        # Get relevant columns and remove duplicates
        subjectsDF = offeredCourses[[
            'sbjNo', 'sbjName', 'sbjlevel', 'sbjNotes', 'elective', 'studyPrg', 'numCurr', 'numSchd'
        ]].drop_duplicates()
        
        def safe_numeric(value):
            """Convert numeric strings with comma decimal separator to float"""
            if pd.isna(value):
                return 0.0
            if isinstance(value, str):
                try:
                    return float(value.replace(',', '.'))
                except ValueError:
                    return 0.0
            return float(value)
        
        subjects = []
        for index, row in subjectsDF.iterrows():
            if pd.isna(row['sbjNo']):
                continue
            
            subject = {
                'S_NR': str(row['sbjNo']),  # Primary key (not auto-increment)
                'S_NAME': str(row['sbjName']) if not pd.isna(row['sbjName']) else None,
                'S_SEMESTER': int(row['sbjlevel']) if not pd.isna(row['sbjlevel']) else None,
                'S_STUPO_HOURS': safe_numeric(row['numCurr']),
                'S_SCHEDULE_HOURS': safe_numeric(row['numSchd']),
                'S_COMMENT': str(row['sbjNotes']) if not pd.isna(row['sbjNotes']) else None,
                'S_TYPE': str(row['elective']) if not pd.isna(row['elective']) else None,
                'S_DEGREE_PROGRAM': str(row['studyPrg']) if not pd.isna(row['studyPrg']) else None
            }
            subjects.append(subject)
        
        # Sort by subject number (same as original)
        subjects = sorted(subjects, key=lambda x: x['S_NR'] or '')
        
        return subjects