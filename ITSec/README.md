# Long story short

If you saved your Lab-Files as stated in the lab tasks, running these commands will generate the document that you need to upload:
```bash
python3 add_filename_to_pdf.py -m 30 -f 15 -c red --pages all --overwrite -r Safety_Lab
python3 combine.py -d output -o combined.pdf -r
python3 combine.py -o ITSec.pdf -f YourLabReport.pdf combined.pdf
```

# PDF Tools Documentation

This documentation covers two Python scripts for PDF manipulation:

1. **PDF Filename Adder**: Add filenames to PDF pages
2. **PDF Merger**: Combine multiple PDFs into a single file

Both tools offer flexible command-line interfaces and support batch processing.

## Table of Contents
- [Requirements](#requirements)
- [PDF Filename Adder](#pdf-filename-adder)
  - [Features](#features)
  - [Command-Line Options](#command-line-options)
  - [Usage Examples](#usage-examples)
- [PDF Merger](#pdf-merger)
  - [Features](#features-1)
  - [Command-Line Options](#command-line-options-1)
  - [Usage Examples](#usage-examples-1)
  - [Bookmark Organization](#bookmark-organization)

## Requirements

Both scripts require Python 3.6+ and the following libraries:

```bash
pip install PyPDF2 reportlab
```

## PDF Filename Adder

The PDF Filename Adder script adds the filename of a PDF to one or more pages within the document. It can process individual files or entire directories of PDFs.

### Features

- Add filename text to PDFs in various positions (top-right, center, etc.)
- Process individual files or entire directories recursively
- Customize text appearance (font size, color, opacity)
- Add custom prefix/suffix to the displayed filename
- Control which pages receive the filename text
- Parallel processing for improved performance

### Command-Line Options

```
usage: add_filename_to_pdf.py [-h] (-f FILES [FILES ...] | -d DIRECTORY) [-o OUTPUT] [-f FONT_SIZE] [-m MARGIN]
                             [-c COLOR] [-p {top-right,top-left,top-center,bottom-right,bottom-left,bottom-center,center}]
                             [--prefix PREFIX] [--suffix SUFFIX] [--font FONT] [--opacity OPACITY]
                             [--pages PAGES] [-r] [-j JOBS] [--overwrite] [--preserve-dates] [--dry-run] [-v]

Add filename to PDF files in the specified position.

required arguments:
  -f, --files FILES [FILES ...]  Specific PDF files to process
  -d, --directory DIRECTORY      Directory containing PDF files to process

output options:
  -o, --output OUTPUT            Output PDF file (for single file) or directory (for multiple files)

text formatting options:
  -f, --font-size FONT_SIZE      Font size for the filename text (default: 10)
  -m, --margin MARGIN            Margin from the edges in points (default: 20)
  -c, --color COLOR              Text color (black, red, blue, green, or #RRGGBB hex code)
  -p, --position {top-right,top-left,top-center,bottom-right,bottom-left,bottom-center,center}
                                 Position of the filename text (default: top-right)
  --prefix PREFIX                Text to add before the filename
  --suffix SUFFIX                Text to add after the filename
  --font FONT                    Path to a TrueType font file (.ttf) to use instead of Helvetica
  --opacity OPACITY              Text opacity (0.0-1.0, default: 1.0)
  --pages PAGES                  Pages to modify: "first", "all", "last", or comma-separated page numbers/ranges (e.g., "1,3-5")

behavior options:
  -r, --recursive                Process PDF files in subdirectories recursively
  -j, --jobs JOBS                Number of parallel jobs (default: 1)
  --overwrite                    Overwrite existing output files
  --preserve-dates               Preserve the original file modification dates
  --dry-run                      List files that would be processed without modifying them
  -v, --verbose                  Print progress information

other options:
  -h, --help                     Show this help message and exit
```

### Usage Examples

**Process a single PDF file:**
```bash
python add_filename_to_pdf.py -f document.pdf -o output.pdf
```

**Process all PDFs in a directory:**
```bash
python add_filename_to_pdf.py -d /path/to/pdfs -o /path/to/output
```

**Customize the appearance:**
```bash
python add_filename_to_pdf.py -f document.pdf -f 12 -c red -p bottom-right --suffix " (DRAFT)"
```

**Add filename to specific pages:**
```bash
python add_filename_to_pdf.py -f document.pdf --pages "1,3-5" -p center
```

**Process PDFs recursively with 4 parallel jobs:**
```bash
python add_filename_to_pdf.py -d /path/to/pdfs -r -j 4 -v -o /path/to/output
```

**Preview processing without making changes:**
```bash
python add_filename_to_pdf.py -d /path/to/pdfs --dry-run -v
```

## PDF Merger

The PDF Merger script combines multiple PDF files into a single document with configurable ordering and bookmark options.

### Features

- Merge PDFs from command-line arguments or directories
- Flexible file ordering options (alphabetical, specified order, or reverse)
- Recursive directory traversal with depth-first ordering
- Hierarchical bookmarks that reflect directory structure
- Option to remove file extensions from bookmark names
- Pattern matching for selecting specific PDFs

### Command-Line Options

```
usage: mergePDFs.py [-h] (-f FILES [FILES ...] | -d DIRECTORY) [-o OUTPUT] [-r] [-p PATTERN]
                    [-l] [--reverse] [-b] [-H] [-e] [-v]

Merge multiple PDF files into a single PDF with customizable ordering.

required arguments:
  -f, --files FILES [FILES ...]  Specific PDF files to merge (in the specified order)
  -d, --directory DIRECTORY      Directory containing PDF files to merge

output options:
  -o, --output OUTPUT            Output PDF file path (default: merged.pdf)

file selection options:
  -r, --recursive                Recursively process subdirectories
  -p, --pattern PATTERN          File pattern to match (default: *.pdf)

behavior options:
  -l, --list-only                List files that would be merged without performing the merge
  --reverse                      Reverse the order of the PDFs

bookmark options:
  -b, --bookmarks                Add bookmarks for each merged PDF
  -H, --hierarchical-bookmarks   Create hierarchical bookmarks based on directory structure (implies --bookmarks)
  -e, --remove-extensions        Remove file extensions from bookmark names

other options:
  -v, --verbose                  Print progress information
  -h, --help                     Show this help message and exit
```

### Usage Examples

**Merge specific PDF files in the given order:**
```bash
python mergePDFs.py -f file1.pdf file2.pdf file3.pdf -o output.pdf
```

**Merge all PDFs in a directory (alphabetically):**
```bash
python mergePDFs.py -d /path/to/pdfs -o merged.pdf
```

**Merge PDFs recursively with bookmarks:**
```bash
python mergePDFs.py -d /path/to/pdfs -r -b -o merged.pdf
```

**Use hierarchical bookmarks reflecting directory structure:**
```bash
python mergePDFs.py -d /path/to/pdfs -r -H -o merged.pdf
```

**Remove file extensions from bookmark names:**
```bash
python mergePDFs.py -d /path/to/pdfs -r -H -e -o merged.pdf
```

**Merge PDFs with a specific pattern:**
```bash
python mergePDFs.py -d /path/to/pdfs -p "report_*.pdf" -o reports.pdf
```

**List files that would be merged without actually merging them:**
```bash
python mergePDFs.py -d /path/to/pdfs -r -l
```

**Merge in reverse order:**
```bash
python mergePDFs.py -d /path/to/pdfs --reverse -o reversed.pdf
```

### Bookmark Organization

The PDF Merger script offers two bookmark modes:

1. **Simple Bookmarks** (`-b`):
   - Creates a flat list of bookmarks
   - Each bookmark points to the first page of the corresponding PDF
   - Bookmarks appear in the same order as the merged PDFs

2. **Hierarchical Bookmarks** (`-H`):
   - Creates a nested bookmark structure that mirrors the directory hierarchy
   - Directories become parent bookmarks
   - PDF files become child bookmarks under their parent directories
   - Follows the same depth-first traversal as the file merging process
   - Optional extension removal (`-e`) makes bookmark names cleaner

Example hierarchy:
```
Reports/
├── 2023/
│   ├── Q1_Report.pdf
│   └── Q2_Report.pdf
└── 2024/
    ├── Q1_Report.pdf
    └── Q2_Report.pdf
```

With hierarchical bookmarks, this would create:
```
Reports
├── 2023
│   ├── Q1_Report.pdf
│   └── Q2_Report.pdf
└── 2024
    ├── Q1_Report.pdf
    └── Q2_Report.pdf
```

With extension removal (`-e`), the leaf bookmarks would appear as:
```
Reports
├── 2023
│   ├── Q1_Report
│   └── Q2_Report
└── 2024
    ├── Q1_Report
    └── Q2_Report
```