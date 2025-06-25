import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class ProfessorpositionExtractor(DataExtractor):
    """Extract professor-position relationships with complex name/title matching"""
    
    @property
    def table_name(self) -> str:
        return "POSITION_PROFESSOR"
    
    @property
    def dependencies(self) -> List[str]:
        return ["TEACHER", "POSITION"]  # Foreign keys to both tables
    
    def extract(self, workload: pd.DataFrame, 
                teacher: List[Dict[str, Any]], 
                position: List[Dict[str, Any]], 
                **kwargs) -> List[Dict[str, Any]]:
        """
        Extract professor positions with name and job title matching.
        Same logic as original getProfessorPositions function.
        """
        # Get relevant columns and remove duplicates
        profPosDF = workload[['reduction', 'term', 'name', 'job title']].drop_duplicates()
        
        # Build lookup dictionaries for efficient matching
        teacher_lookup = {}
        for teacher_record in teacher:
            lastname = str(teacher_record.get('T_LASTNAME') or '').lower().strip()
            if lastname:
                teacher_lookup[lastname] = teacher_record['T_ID']
        
        position_lookup = {}
        for position_record in position:
            pos_name = str(position_record.get('PO_NAME') or '').strip()
            if pos_name:
                position_lookup[pos_name] = position_record['PO_ID']
        
        def safe_numeric(value):
            """Convert numeric strings with comma decimal separator to float"""
            if pd.isna(value):
                return None
            if isinstance(value, str):
                try:
                    return float(value.replace(',', '.'))
                except ValueError:
                    return None
            return float(value)
        
        prof_positions = []
        for index, row in profPosDF.iterrows():
            professor_id = None
            position_id = None
            
            # Find professor by name matching (same as original logic)
            if not pd.isna(row['name']) and isinstance(row['name'], str):
                name_lower = str(row['name']).lower().strip()
                
                # Look for name match in teacher lastnames
                for lastname, teacher_id in teacher_lookup.items():
                    if name_lower and lastname and name_lower in lastname:
                        professor_id = teacher_id
                        break
            
            # Find position by exact job title match (same as original)
            if not pd.isna(row['job title']) and isinstance(row['job title'], str):
                job_title = str(row['job title']).strip()
                position_id = position_lookup.get(job_title)
            
            # Only create record if both foreign keys are found
            if professor_id and position_id:
                prof_pos = {
                    'P_ID': professor_id,  # Foreign key to PROFESSOR.P_ID (which equals TEACHER.T_ID)
                    'CREDITED_HOURS': safe_numeric(row['reduction']),
                    'PO_ID': position_id,  # Foreign key to POSITION.PO_ID
                    'TERM': str(row['term']) if not pd.isna(row['term']) else None
                }
                prof_positions.append(prof_pos)
        
        return prof_positions