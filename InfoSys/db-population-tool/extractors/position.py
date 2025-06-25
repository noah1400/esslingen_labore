import pandas as pd
from typing import Dict, List, Any
from base_extractor import DataExtractor

class PositionExtractor(DataExtractor):
    """Extract positions with auto-incrementing IDs from workload data"""
    
    @property
    def table_name(self) -> str:
        return "POSITION"
    
    def extract(self, workload: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
        """
        Extract unique job titles and assign auto-incrementing IDs.
        Same logic as original getPositions function.
        """
        # Get unique job titles, remove duplicates and nulls
        positions = workload['job title'].drop_duplicates().dropna().tolist()
        
        result = []
        for i, position in enumerate(positions, 1):  # Start auto-increment at 1
            if position and str(position).strip():
                result.append({
                    'PO_ID': i,  # Auto-incrementing ID
                    'PO_NAME': str(position).strip()
                })
        
        return result