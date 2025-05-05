#!/usr/bin/env python3
import os
import sys
import argparse
import fnmatch
from pathlib import Path
from PyPDF2 import PdfWriter, PdfReader

def collect_pdfs_from_args(file_args):
    """Collect PDF files directly specified in command-line arguments"""
    pdf_files = []
    
    for path in file_args:
        if os.path.isfile(path) and path.lower().endswith('.pdf'):
            pdf_files.append((path, os.path.basename(path), None))  # (path, name, parent)
        else:
            print(f"Warning: Skipping non-PDF file: {path}")
    
    return pdf_files

def collect_pdfs_from_directory(directory, recursive=False):
    """
    Collect PDF files from a directory with appropriate ordering and structure information:
    - Non-recursive: Alphabetical by filename
    - Recursive: Depth-first traversal, with directories and files sorted alphabetically
    
    Returns a list of tuples: (file_path, display_name, parent_path)
    """
    pdf_files = []
    root_path = Path(directory).resolve()
    
    if not recursive:
        # Simple case: collect all PDFs in this directory, sorted alphabetically
        pdf_files = [
            (str(f), f.name, None) for f in sorted(root_path.glob('*.pdf'))
        ]
    else:
        # Recursive case: depth-first traversal with hierarchy information
        def dfs_collect_pdfs(path, parent=None):
            result = []
            
            # Get all immediate contents of this directory
            contents = list(path.iterdir())
            
            # Separate directories and files
            directories = sorted([item for item in contents if item.is_dir()])
            files = sorted([item for item in contents if item.is_file() and item.suffix.lower() == '.pdf'])
            
            # Current directory as parent for subdirectories
            current_dir_name = path.name
            current_dir_path = str(path.relative_to(root_path)) if path != root_path else ""
            
            # Process subdirectories first (depth-first, alphabetically sorted)
            for subdir in directories:
                sub_results = dfs_collect_pdfs(subdir, current_dir_path)
                result.extend(sub_results)
            
            # Then add files from this directory (alphabetically sorted)
            for file in files:
                result.append((
                    str(file),                  # Full file path
                    file.name,                  # Display name (filename)
                    current_dir_path            # Parent folder (for bookmark hierarchy)
                ))
            
            return result
        
        pdf_files = dfs_collect_pdfs(root_path)
    
    return pdf_files

def get_bookmark_name(filename, remove_extension=False):
    """Get the bookmark name from a filename, optionally removing the extension"""
    if remove_extension:
        return os.path.splitext(filename)[0]
    return filename

def merge_pdfs(pdf_files, output_path, add_bookmarks=False, hierarchical_bookmarks=False, 
              remove_extensions=False, verbose=False):
    """Merge multiple PDF files into a single output PDF with optional hierarchical bookmarks"""
    if not pdf_files:
        print("Error: No PDF files found to merge.")
        return False
    
    try:
        merger = PdfWriter()
        
        # Track current page number for bookmarks
        current_page = 0
        bookmarks = {}
        bookmark_hierarchy = {}
        
        # Process each PDF file
        for file_info in pdf_files:
            file_path, display_name, parent_path = file_info
            
            # Get bookmark name (with or without extension)
            bookmark_name = get_bookmark_name(display_name, remove_extensions)
            
            if verbose:
                print(f"Adding: {file_path}")
            
            try:
                reader = PdfReader(file_path)
                
                # Check if PDF is encrypted
                if reader.is_encrypted:
                    print(f"Warning: Skipping encrypted PDF: {file_path}")
                    continue
                
                start_page = current_page
                
                # Add all pages from this PDF
                for page in reader.pages:
                    merger.add_page(page)
                    current_page += 1
                
                # Store bookmark information if requested
                if add_bookmarks and current_page > start_page:
                    # For hierarchical bookmarks, we need to track parent info
                    if hierarchical_bookmarks and parent_path:
                        # Add parent directory to hierarchy if not already present
                        parts = parent_path.split(os.sep)
                        current_parent = ""
                        
                        # Build the directory hierarchy
                        for i, part in enumerate(parts):
                            if not part:  # Skip empty parts
                                continue
                                
                            prev_parent = current_parent
                            current_parent = os.path.join(current_parent, part) if current_parent else part
                            
                            # Add this directory level if not already in the hierarchy
                            if current_parent not in bookmark_hierarchy:
                                bookmark_hierarchy[current_parent] = {
                                    'title': part,
                                    'parent': prev_parent if prev_parent else None,
                                    'is_file': False,
                                    'page': None  # Directories don't point to specific pages
                                }
                        
                        # Add the file itself with its parent directory
                        bookmarks[start_page] = {
                            'title': bookmark_name,
                            'parent': parent_path,
                            'is_file': True,
                            'page': start_page
                        }
                    else:
                        # Simple flat bookmarks
                        bookmarks[start_page] = bookmark_name
                
                # Add document metadata (from the first PDF)
                if len(merger.pages) == len(reader.pages):
                    try:
                        metadata = reader.metadata
                        if metadata:
                            merger.add_metadata(metadata)
                    except Exception as e:
                        print(f"Warning: Could not copy metadata from {file_path}: {str(e)}")
                
            except Exception as e:
                print(f"Error processing file {file_path}: {str(e)}")
                continue
        
        # Check if we have any pages to write
        if len(merger.pages) == 0:
            print("Error: No PDF pages could be merged.")
            return False
        
        # Add bookmarks if requested
        if add_bookmarks:
            if hierarchical_bookmarks:
                # First, add all directories (which won't have page numbers)
                created_bookmarks = {}
                
                # Helper function to create a bookmark and its parent chain
                def create_bookmark_with_parents(bookmark_id, info):
                    if bookmark_id in created_bookmarks:
                        return created_bookmarks[bookmark_id]
                    
                    # If it has a parent, make sure the parent exists first
                    parent_ref = None
                    if info['parent'] and info['parent'] in bookmark_hierarchy:
                        parent_info = bookmark_hierarchy[info['parent']]
                        parent_ref = create_bookmark_with_parents(info['parent'], parent_info)
                    
                    # Now create this bookmark
                    bookmark_ref = merger.add_outline_item(
                        info['title'], 
                        info['page'] if info['page'] is not None else 0,
                        parent=parent_ref
                    )
                    created_bookmarks[bookmark_id] = bookmark_ref
                    
                    if verbose and info['is_file']:
                        print(f"Added bookmark: '{info['title']}' under '{info['parent']}' -> page {info['page']+1}")
                    
                    return bookmark_ref
                
                # Add directory bookmarks first
                for dir_path, dir_info in bookmark_hierarchy.items():
                    if dir_path not in created_bookmarks:
                        create_bookmark_with_parents(dir_path, dir_info)
                
                # Then add file bookmarks
                for page_num, file_info in bookmarks.items():
                    if file_info['is_file']:
                        create_bookmark_with_parents(page_num, file_info)
                
                if verbose:
                    print(f"Added {len(bookmarks)} file bookmarks and {len(bookmark_hierarchy)} directory bookmarks")
            else:
                # Simple flat bookmarks
                for page_num, title in bookmarks.items():
                    merger.add_outline_item(title, page_num)
                    if verbose:
                        print(f"Added bookmark: '{title}' -> page {page_num+1}")
                
                if verbose:
                    print(f"Added {len(bookmarks)} bookmarks")
        
        # Create output directory if it doesn't exist
        output_dir = os.path.dirname(output_path)
        if output_dir and not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        # Write the merged PDF
        with open(output_path, 'wb') as f:
            merger.write(f)
        
        if verbose:
            print(f"Successfully merged {len(pdf_files)} PDFs with {len(merger.pages)} pages into: {output_path}")
        
        return True
    
    except Exception as e:
        print(f"Error merging PDFs: {str(e)}")
        return False

def list_files_only(pdf_files, verbose=False, remove_extensions=False):
    """List the files that would be merged without actually merging them"""
    if not pdf_files:
        print("No PDF files found to merge.")
        return
    
    print(f"Found {len(pdf_files)} PDF files that would be merged (in this order):")
    for i, file_info in enumerate(pdf_files, 1):
        file_path, display_name, parent_path = file_info
        bookmark_name = get_bookmark_name(display_name, remove_extensions)
        
        if parent_path:
            print(f"{i}. {parent_path}/{bookmark_name} ({file_path})")
        else:
            print(f"{i}. {bookmark_name} ({file_path})")

def main():
    parser = argparse.ArgumentParser(description='Merge multiple PDF files into a single PDF with customizable ordering.')
    
    # Input options
    input_group = parser.add_mutually_exclusive_group(required=True)
    input_group.add_argument('-f', '--files', nargs='+', help='Specific PDF files to merge (in the specified order)')
    input_group.add_argument('-d', '--directory', help='Directory containing PDF files to merge')
    
    # Output options
    parser.add_argument('-o', '--output', default='merged.pdf', help='Output PDF file path (default: merged.pdf)')
    
    # Behavior options
    parser.add_argument('-r', '--recursive', action='store_true', help='Recursively process subdirectories')
    parser.add_argument('-p', '--pattern', default='*.pdf', help='File pattern to match (default: *.pdf)')
    parser.add_argument('-l', '--list-only', action='store_true', help='List files that would be merged without performing the merge')
    parser.add_argument('--reverse', action='store_true', help='Reverse the order of the PDFs')
    parser.add_argument('-b', '--bookmarks', action='store_true', help='Add bookmarks for each merged PDF')
    parser.add_argument('-H', '--hierarchical-bookmarks', action='store_true', 
                        help='Create hierarchical bookmarks based on directory structure (implies --bookmarks)')
    parser.add_argument('-e', '--remove-extensions', action='store_true',
                        help='Remove file extensions from bookmark names')
    parser.add_argument('-v', '--verbose', action='store_true', help='Print detailed progress information')
    
    args = parser.parse_args()
    
    # Hierarchical bookmarks imply bookmarks enabled
    if args.hierarchical_bookmarks:
        args.bookmarks = True
    
    # Collect PDF files based on input options
    pdf_files = []
    
    if args.files:
        pdf_files = collect_pdfs_from_args(args.files)
    elif args.directory:
        if not os.path.isdir(args.directory):
            print(f"Error: Directory not found: {args.directory}")
            return 1
        
        pdf_files = collect_pdfs_from_directory(args.directory, args.recursive)
        
        # Apply pattern matching if specified
        if args.pattern and args.pattern != '*.pdf':
            pdf_files = [f for f in pdf_files if fnmatch.fnmatch(f[1], args.pattern)]
    
    # Reverse order if requested
    if args.reverse:
        pdf_files.reverse()
    
    # List files only or perform the merge
    if args.list_only:
        list_files_only(pdf_files, args.verbose, args.remove_extensions)
        return 0
    
    # Perform the merge
    success = merge_pdfs(
        pdf_files, 
        args.output, 
        args.bookmarks, 
        args.hierarchical_bookmarks,
        args.remove_extensions,
        args.verbose
    )
    
    return 0 if success else 1

if __name__ == "__main__":
    sys.exit(main())