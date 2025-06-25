# Database Population Tools - Student Guide

## Setup

### Required Files Structure
```
your-project/
├── simple_db_populator.py
├── extractor_generator.py
├── data/                    # Put your CSV files here
│   ├── teachers.csv
│   ├── courses.csv
│   └── grades.csv
├── extractors/              # Generated extractor files go here
│   ├── base_extractor.py    # Required base class
│   ├── teacher.py          # Generated extractors
│   └── course.py
└── generated_inserts.sql    # Output file
```

**The current content of the extractors directory represents the structure of our group. These files can be safely deleted or used as a reference ( all but the `base_extractor.py` !!!). If you do not delete the extractors the populator tool will generate inserts statements for tables that might not exist in you case.** 

### Quick Start
1. Create folders: `mkdir data extractors`
2. Copy the two Python tools to your project
3. Create `extractors/base_extractor.py` with the base class
4. If you have a excel file save each worksheet in the file as a seperate csv file
5. Put your CSV files in the `data/` folder

---

## Adding New Tables

### Step 1: Generate the Extractor
```bash
# Basic table (data from one CSV)
python3 extractor_generator.py TEACHER

# Table with dependencies (has foreign keys)
python3 extractor_generator.py LECTURER --deps TEACHER

# Table using multiple CSV files
python3 extractor_generator.py PROFESSOR --csv offeredCourses,workload --deps TEACHER
```

### Step 2: Implement the Logic
1. Open the generated file (e.g., `extractors/teacher.py`)
2. Find the `extract()` method
3. Replace the TODO comments with your data transformation logic
4. Save the file

The extract function returns a list of dictionaries. Each entry of that lists represents one entry in the table.

### Step 3: Generate SQL
```bash
python3 simple_db_populator.py --data-dir data --schema "YOUR_SCHEMA"
```

---

## When to Use Dependencies

### Use dependencies when your table has **foreign keys** that reference other tables.

**Example Database Schema:**
```sql
STUDENT (ID, NAME, DEPARTMENT_ID)  -- DEPARTMENT_ID references DEPARTMENT
COURSE (ID, NAME, PROFESSOR_ID)    -- PROFESSOR_ID references PROFESSOR  
ENROLLMENT (STUDENT_ID, COURSE_ID) -- Both are foreign keys
```

**Correct Dependency Setup:**
```bash
# STUDENT depends on DEPARTMENT
python3 extractor_generator.py STUDENT --deps DEPARTMENT

# COURSE depends on PROFESSOR
python3 extractor_generator.py COURSE --deps PROFESSOR

# ENROLLMENT depends on both STUDENT and COURSE
python3 extractor_generator.py ENROLLMENT --deps STUDENT,COURSE
```

### Why Dependencies Matter
- Dependencies ensure tables are processed in the correct order
- Foreign key values are available when you need them
- Prevents database constraint violations

---

## When to Use the `--csv` argument

It is recommended to always use the `--csv` argument and specify where the data for that table is coming from.
Using the `--csv` parameter will include the csv data in the `extract()` function so you can use it.

### Use `--csv` when your table data comes from **multiple CSV sources**.

**Scenario 1: Related Data Split Across Files**
```bash
# Professor data spread across two files:
# - faculty.csv: basic info (ID, name, department)
# - workload.csv: teaching assignments (professor_id, course_hours)
python3 extractor_generator.py PROFESSOR --csv faculty,workload
```

**Scenario 2: Main Data + Lookup Tables**
```bash
# Student data with grade mappings:
# - students.csv: main student data
# - grade_scale.csv: grade conversion rules
python3 extractor_generator.py STUDENT --csv students,grade_scale
```

**Generated Function Signature:**
```python
def extract(self, faculty: pd.DataFrame, workload: pd.DataFrame, **kwargs):
    # You can access both CSV files as DataFrames
    for _, row in faculty.iterrows():
        # Process faculty data
        
    for _, row in workload.iterrows():
        # Process workload data
```

---

## CSV File Guidelines

### File Placement
- **Always** put CSV files in the `data/` folder
- Name files descriptively: `students.csv`, `course_offerings.csv`
- Use consistent naming (avoid spaces, special characters)

### CSV Format Requirements
- First row must contain column headers
- Use either comma (`,`) or semicolon (`;`) as delimiter
- UTF-8 encoding recommended
- No blank rows at the start or end

### File Naming in Commands
```bash
# If your file is data/course_offerings.csv
python3 extractor_generator.py COURSE --csv course_offerings

# Multiple files
python3 extractor_generator.py STUDENT --csv students,student_addresses
```

---

## Working with Generated Extractors

### Basic Implementation Example
```python
# extractors/student.py
def extract(self, students: pd.DataFrame, **kwargs) -> List[Dict[str, Any]]:
    records = []
    
    for _, row in students.iterrows():
        record = {
            'STUDENT_ID': int(row['id']),           # Map CSV column to DB column
            'FIRST_NAME': str(row['first_name']),
            'LAST_NAME': str(row['last_name']),
            'EMAIL': str(row['email']),
            'ENROLLMENT_DATE': row['enrollment_date']
        }
        records.append(record)
    
    return records
```

### Using Dependencies (Foreign Keys)
```python
# extractors/enrollment.py  
def extract(self, enrollments: pd.DataFrame, 
           student: List[Dict[str, Any]],      # Dependency data
           course: List[Dict[str, Any]],       # Dependency data
           **kwargs) -> List[Dict[str, Any]]:
    
    # Create lookup dictionaries for foreign keys
    student_lookup = {s['STUDENT_ID']: s for s in student}
    course_lookup = {c['COURSE_ID']: c for c in course}
    
    records = []
    for _, row in enrollments.iterrows():
        student_id = int(row['student_id'])
        course_id = int(row['course_id'])
        
        # Validate foreign keys exist
        if student_id in student_lookup and course_id in course_lookup:
            record = {
                'STUDENT_ID': student_id,
                'COURSE_ID': course_id,
                'ENROLLMENT_DATE': row['date'],
                'GRADE': row.get('grade', None)
            }
            records.append(record)
    
    return records
```

---

## Command Reference

### Extractor Generator
```bash
# Basic syntax
python3 extractor_generator.py TABLE_NAME [options]

# Options
--csv FILE1,FILE2      # Specify CSV input files
--deps TABLE1,TABLE2   # Specify dependency tables  
--dry-run             # Preview without creating files
--overwrite           # Replace existing extractor
```

### Database Populator
```bash
# Basic syntax  
python3 simple_db_populator.py [options]

# Options
--data-dir PATH       # CSV files directory (default: data)
--extractors PATH     # Extractors directory (default: extractors)
--schema NAME         # Database schema name (default: None)
--output FILE         # SQL output file (default: generated_inserts.sql)
```

---

## Common Usage Patterns

### Pattern 1: Simple Independent Table
```bash
python3 extractor_generator.py DEPARTMENT
# Edit extractors/department.py
python3 simple_db_populator.py
```

### Pattern 2: Table with Foreign Key
```bash
python3 extractor_generator.py STUDENT --deps DEPARTMENT
# Edit extractors/student.py to handle department_id foreign key
python3 simple_db_populator.py
```

### Pattern 3: Junction Table (Many-to-Many)
```bash
python3 extractor_generator.py STUDENT_COURSE --deps STUDENT,COURSE
# Edit extractors/student_course.py to handle both foreign keys
python3 simple_db_populator.py
```

### Pattern 4: Complex Table with Multiple Data Sources
```bash
python3 extractor_generator.py PROFESSOR --csv faculty,teaching_loads,research --deps DEPARTMENT
# Edit extractors/professor.py to combine data from all three CSV files
python3 simple_db_populator.py
```

---

## Troubleshooting

### "No extractors found"
- Check that `extractors/base_extractor.py` exists
- Verify your extractor files inherit from `DataExtractor`
- Ensure extractor class names end with "Extractor"

### "Circular dependency detected"
- Review your dependency chains
- A table cannot depend on itself
- Check for dependency loops (A→B→C→A)

### "CSV file not found"
- Verify files are in the `data/` directory
- Check file names match what you specified in `--csv`
- Ensure CSV files have the `.csv` extension

### "Foreign key errors in generated SQL"
- Check that dependency tables are extracted successfully
- Verify foreign key values exist in referenced tables
- Review your foreign key lookup logic in extractors

---

## How It Works (Technical Overview)

### System Architecture
The system consists of two main components:

1. **Extractor Generator**: Creates template code for data transformation
2. **Database Populator**: Executes extractors and generates SQL

### Processing Flow
1. **Discovery**: Populator scans `extractors/` folder for extractor classes
2. **Dependency Analysis**: Builds dependency graph from extractor declarations
3. **Topological Sort**: Orders extractors to satisfy foreign key constraints
4. **Data Extraction**: Executes extractors in dependency order
5. **SQL Generation**: Creates INSERT statements with proper schema qualification

### Key Design Principles
- **Plugin Architecture**: Extractors are independent, discoverable modules
- **Dependency Injection**: CSV data and dependencies passed as parameters
- **Fail-Fast Validation**: Early error detection with clear messages
- **Atomic Operations**: Safe file operations with rollback capability

### Security Features
- Input validation against SQL injection patterns
- Path traversal protection for file operations
- Safe SQL value escaping in generated statements
- Atomic file writes to prevent corruption