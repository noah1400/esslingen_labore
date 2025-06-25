import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class CourseExtractor(DataExtractor):
    """Extract courses with auto-incrementing IDs and foreign key validation"""
    
    @property
    def table_name(self) -> str:
        return "COURSE"
    
    @property
    def dependencies(self) -> List[str]:
        return ["TEACHER", "SUBJECT"]  # Foreign keys to both tables
    
    def extract(self, offeredCourses: pd.DataFrame, 
                teacher: List[Dict[str, Any]], 
                subject: List[Dict[str, Any]], 
                **kwargs) -> List[Dict[str, Any]]:
        """
        Extract courses with validation against existing teachers and subjects.
        Same logic as original getCourses function.
        """
        # Get relevant columns and remove duplicates
        coursesDF = offeredCourses[[
            'lecNo', 'sbjNo', 'assNotes', 'term', 'cntCurr', 'cntLec', 'cntSchd'
        ]].drop_duplicates()
        
        # Create lookup sets for validation (same as original)
        valid_teacher_ids = {t['T_ID'] for t in teacher}
        valid_subject_nrs = {s['S_NR'] for s in subject}
        
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
        
        courses = []
        for index, row in coursesDF.iterrows():
            # Skip rows with missing required data
            if pd.isna(row['lecNo']) or pd.isna(row['sbjNo']):
                continue
            
            teacher_id = int(row['lecNo'])
            subject_nr = str(row['sbjNo'])
            
            # Validate foreign keys (same as original logic)
            if teacher_id not in valid_teacher_ids:
                continue  # Skip courses with invalid teacher
            
            if subject_nr not in valid_subject_nrs:
                continue  # Skip courses with invalid subject
            
            course = {
                'C_ID': index + 1,  # Auto-incrementing ID (same as original)
                'C_TEACHER': teacher_id,  # Foreign key to TEACHER.T_ID
                'C_SUBJECT': subject_nr,  # Foreign key to SUBJECT.S_NR
                'C_ACTUAL_STUPO_HOURS': safe_numeric(row['cntCurr']),
                'C_ACTUAL_SCHEDULE_HOURS': safe_numeric(row['cntSchd']),
                'C_CREDITED_HOURS': safe_numeric(row['cntLec']),
                'C_TEACHER_COMMENT': str(row['assNotes']) if not pd.isna(row['assNotes']) else None,
                'C_SEMESTER': str(row['term']) if not pd.isna(row['term']) else None
            }
            courses.append(course)
        
        return courses