import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class LecturerExtractor(DataExtractor):
    """Extract lecturers (teachers where isprof = 'FALSCH') with supervisor lookup"""
    
    @property
    def table_name(self) -> str:
        return "LECTURER"
    
    @property
    def dependencies(self) -> List[str]:
        return ["TEACHER"]  # Need teachers data for supervisor lookup
    
    def extract(self, offeredCourses: pd.DataFrame, teacher: List[Dict[str, Any]], **kwargs) -> List[Dict[str, Any]]:
        """
        Extract lecturers and resolve supervisor foreign keys.
        Same logic as original getLecturers function with name-based supervisor lookup.
        """
        # Filter for lecturers only (non-professors)
        lecturersDF = offeredCourses[
            offeredCourses['isprof'] == False
        ][['lecNo', 'supervisor']].drop_duplicates()
        
        lecturers = []
        for index, row in lecturersDF.iterrows():
            if pd.isna(row['lecNo']):
                continue
            
            # Find supervisor using name matching (same as original logic)
            supervisor = None
            if not pd.isna(row['supervisor']) and isinstance(row['supervisor'], str):
                supervisor_name = str(row['supervisor']).lower().strip()
                
                # Search through teachers for name matches
                for teacher_record in teacher:
                    teacher_name = str(teacher_record.get('T_NAME') or '').lower().strip()
                    teacher_lastname = str(teacher_record.get('T_LASTNAME') or '').lower().strip()
                    
                    # Check if supervisor name matches teacher's first name or last name
                    if (supervisor_name and teacher_name and supervisor_name in teacher_name) or \
                       (supervisor_name and teacher_lastname and supervisor_name in teacher_lastname):
                        supervisor = teacher_record['T_ID']
                        break
            
            lecturer = {
                'L_ID': int(row['lecNo']),  # References TEACHER.T_ID
                'L_STREET_ADDRESS': None,  # Default null as in original
                'L_CITY': None,           # Default null as in original
                'L_ZIP': None,            # Default null as in original
                'L_SUPERVISOR': supervisor # Foreign key to TEACHER.T_ID
            }
            lecturers.append(lecturer)
        
        # Sort by ID (same as original)
        lecturers = sorted(lecturers, key=lambda x: x['L_ID'])
        
        return lecturers