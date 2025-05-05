import os
import sys
import argparse
import shutil
from concurrent.futures import ProcessPoolExecutor
from PyPDF2 import PdfReader, PdfWriter
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from reportlab.lib.colors import Color, black, red, blue, green
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from io import BytesIO

def parse_color(color_str):
    """Convert a color string to a reportlab color object"""
    color_map = {
        'black': black,
        'red': red,
        'blue': blue,
        'green': green,
    }
    
    if color_str in color_map:
        return color_map[color_str]
    
    # Try to parse as hex color (#RRGGBB)
    if color_str.startswith('#') and len(color_str) == 7:
        try:
            r = int(color_str[1:3], 16) / 255
            g = int(color_str[3:5], 16) / 255
            b = int(color_str[5:7], 16) / 255
            return Color(r, g, b)
        except ValueError:
            pass
    
    # Default to black if color is not recognized
    return black

def get_position_coordinates(position, page_width, page_height, text_width, font_size, margin):
    """Calculate coordinates based on position keyword"""
    positions = {
        'top-right': (page_width - text_width - margin, page_height - margin),
        'top-left': (margin, page_height - margin),
        'top-center': ((page_width - text_width) / 2, page_height - margin),
        'bottom-right': (page_width - text_width - margin, margin + font_size),
        'bottom-left': (margin, margin + font_size),
        'bottom-center': ((page_width - text_width) / 2, margin + font_size),
        'center': ((page_width - text_width) / 2, page_height / 2)
    }
    
    return positions.get(position, positions['top-right'])

def register_custom_font(font_path):
    """Register a custom font if provided"""
    if not font_path:
        return "Helvetica"
    
    try:
        font_name = os.path.splitext(os.path.basename(font_path))[0]
        pdfmetrics.registerFont(TTFont(font_name, font_path))
        return font_name
    except Exception as e:
        print(f"Error loading custom font: {str(e)}")
        return "Helvetica"

def add_filename_to_pdf(input_pdf_path, output_pdf_path=None, font_size=10, margin=20, 
                        text_color=black, position='top-right', prefix='', suffix='',
                        font_path=None, opacity=1.0, pages='first'):
    """Add the filename to specified pages of a PDF file"""
    # Get the filename without the path
    filename = os.path.basename(input_pdf_path)
    display_text = f"{prefix}{filename}{suffix}"
    
    try:
        # Read the original PDF
        pdf_reader = PdfReader(input_pdf_path)
        
        # Check if the PDF is encrypted
        if pdf_reader.is_encrypted:
            print(f"Error: The PDF file '{input_pdf_path}' is encrypted and cannot be modified.")
            return False
        
        pdf_writer = PdfWriter()
        
        # Determine which pages to modify
        pages_to_modify = []
        if pages == 'first':
            pages_to_modify = [0]
        elif pages == 'all':
            pages_to_modify = range(len(pdf_reader.pages))
        elif pages == 'last':
            pages_to_modify = [len(pdf_reader.pages) - 1]
        else:
            # Parse comma-separated page numbers (1-based to 0-based)
            try:
                for page_str in pages.split(','):
                    if '-' in page_str:
                        start, end = map(int, page_str.split('-'))
                        pages_to_modify.extend(range(start-1, end))
                    else:
                        pages_to_modify.append(int(page_str) - 1)
            except ValueError:
                print(f"Error: Invalid page specification '{pages}'. Using first page only.")
                pages_to_modify = [0]
        
        # Register custom font if provided
        font_name = register_custom_font(font_path)
        
        # Process each page
        for page_num in range(len(pdf_reader.pages)):
            page = pdf_reader.pages[page_num]
            
            if page_num in pages_to_modify:
                # Get page dimensions
                page_width = float(page.mediabox.width)
                page_height = float(page.mediabox.height)
                
                # Create a temporary PDF with the filename text
                packet = BytesIO()
                can = canvas.Canvas(packet)
                
                # Set the canvas size to match the PDF page size
                can.setPageSize((page_width, page_height))
                
                # Add the filename text
                can.setFont(font_name, font_size)
                text_width = can.stringWidth(display_text, font_name, font_size)
                
                # Set text position based on the specified position
                x, y = get_position_coordinates(position, page_width, page_height, 
                                              text_width, font_size, margin)
                
                # Set text color and opacity
                can.setFillColor(text_color)
                can.setFillAlpha(opacity)
                
                can.drawString(x, y, display_text)
                can.save()
                
                # Move to the beginning of the BytesIO buffer
                packet.seek(0)
                
                # Create a PDF reader for the temporary PDF with the text
                text_watermark = PdfReader(packet)
                
                # Merge the text with the page
                page.merge_page(text_watermark.pages[0])
            
            # Add the page to the writer
            pdf_writer.add_page(page)
        
        # Write the modified PDF to the output file
        with open(output_pdf_path, "wb") as output_file:
            pdf_writer.write(output_file)
        
        return True
    
    except Exception as e:
        print(f"Error processing PDF '{input_pdf_path}': {str(e)}")
        return False

def process_file(args, input_file, output_dir):
    """Process a single PDF file with the given arguments"""
    # Skip if not a PDF file
    if not input_file.lower().endswith('.pdf'):
        if args.verbose:
            print(f"Skipping non-PDF file: {input_file}")
        return False
    
    # Create output path
    rel_path = os.path.relpath(input_file, args.input) if os.path.isdir(args.input) else os.path.basename(input_file)
    output_file = os.path.join(output_dir, rel_path)
    
    # Create subdirectories if needed
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    # Check if output file already exists
    if os.path.exists(output_file) and not args.overwrite:
        if args.verbose:
            print(f"Skipping existing file: {output_file}")
        return False
    
    if args.dry_run:
        print(f"Would process: {input_file} -> {output_file}")
        return True
    
    if args.verbose:
        print(f"Processing: {input_file}")
    
    # Process the file
    success = add_filename_to_pdf(
        input_file, 
        output_file, 
        font_size=args.font_size, 
        margin=args.margin,
        text_color=parse_color(args.color),
        position=args.position,
        prefix=args.prefix,
        suffix=args.suffix,
        font_path=args.font,
        opacity=args.opacity,
        pages=args.pages
    )
    
    # Preserve modification time if requested
    if success and args.preserve_dates:
        shutil.copystat(input_file, output_file)
    
    return success

def find_pdf_files(directory, recursive=False):
    """Find all PDF files in a directory"""
    pdf_files = []
    
    if recursive:
        for root, _, files in os.walk(directory):
            for file in files:
                if file.lower().endswith('.pdf'):
                    pdf_files.append(os.path.join(root, file))
    else:
        for file in os.listdir(directory):
            if file.lower().endswith('.pdf'):
                pdf_files.append(os.path.join(directory, file))
    
    return pdf_files

def main():
    parser = argparse.ArgumentParser(description='Add filename to PDF files in the specified position.')
    parser.add_argument('input', help='Input PDF file or directory containing PDF files')
    parser.add_argument('-o', '--output', help='Output PDF file (for single file) or directory (for multiple files)')
    parser.add_argument('-f', '--font-size', type=int, default=10, help='Font size for the filename text (default: 10)')
    parser.add_argument('-m', '--margin', type=int, default=20, help='Margin from the edges in points (default: 20)')
    parser.add_argument('-c', '--color', default='black', help='Text color (black, red, blue, green, or #RRGGBB hex code)')
    parser.add_argument('-p', '--position', default='top-right', 
                        choices=['top-right', 'top-left', 'top-center', 'bottom-right', 'bottom-left', 'bottom-center', 'center'],
                        help='Position of the filename text (default: top-right)')
    parser.add_argument('--prefix', default='', help='Text to add before the filename')
    parser.add_argument('--suffix', default='', help='Text to add after the filename')
    parser.add_argument('--font', help='Path to a TrueType font file (.ttf) to use instead of Helvetica')
    parser.add_argument('--opacity', type=float, default=1.0, help='Text opacity (0.0-1.0, default: 1.0)')
    parser.add_argument('--pages', default='first', help='Pages to modify: "first", "all", "last", or comma-separated page numbers/ranges (e.g., "1,3-5")')
    parser.add_argument('-r', '--recursive', action='store_true', help='Process PDF files in subdirectories recursively')
    parser.add_argument('-j', '--jobs', type=int, default=1, help='Number of parallel jobs (default: 1)')
    parser.add_argument('--overwrite', action='store_true', help='Overwrite existing output files')
    parser.add_argument('--preserve-dates', action='store_true', help='Preserve the original file modification dates')
    parser.add_argument('--dry-run', action='store_true', help='List files that would be processed without modifying them')
    parser.add_argument('-v', '--verbose', action='store_true', help='Print progress information')
    
    args = parser.parse_args()
    
    # Determine input and output paths
    input_path = args.input
    
    # Check if input exists
    if not os.path.exists(input_path):
        print(f"Error: The specified input '{input_path}' does not exist.")
        return 1
    
    # Determine if we're processing a single file or a directory
    is_single_file = os.path.isfile(input_path)
    
    # Determine output path
    output_path = args.output
    if not output_path:
        if is_single_file:
            # Default output for a single file: input_filename_with_filename.pdf
            base_name = os.path.splitext(input_path)[0]
            ext = os.path.splitext(input_path)[1]
            output_path = f"{base_name}_with_filename{ext}"
        else:
            # Default output for a directory: ./output/
            output_path = os.path.join(os.getcwd(), "output")
    
    # Create output directory if it doesn't exist
    if not is_single_file or os.path.isdir(output_path):
        os.makedirs(output_path, exist_ok=True)
    elif not os.path.exists(os.path.dirname(output_path)):
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
    
    # Process files
    if is_single_file:
        # Process a single file
        if args.verbose:
            print(f"Processing single file: {input_path}")
        
        success = process_file(args, input_path, os.path.dirname(output_path) if not os.path.isdir(output_path) else output_path)
        
        if args.verbose:
            if success and not args.dry_run:
                print(f"Added filename to PDF. Output saved to: {output_path}")
            elif not success and not args.dry_run:
                print(f"Failed to process file: {input_path}")
        
        return 0 if success else 1
    else:
        # Process a directory of files
        pdf_files = find_pdf_files(input_path, args.recursive)
        
        if not pdf_files:
            print(f"No PDF files found in {input_path}")
            return 1
        
        if args.verbose:
            print(f"Found {len(pdf_files)} PDF files to process")
        
        if args.jobs > 1 and not args.dry_run:
            # Process files in parallel
            succeeded = 0
            with ProcessPoolExecutor(max_workers=args.jobs) as executor:
                results = list(executor.map(lambda file: process_file(args, file, output_path), pdf_files))
                succeeded = sum(1 for result in results if result)
        else:
            # Process files sequentially
            succeeded = sum(1 for file in pdf_files if process_file(args, file, output_path))
        
        if args.verbose:
            if not args.dry_run:
                print(f"Successfully processed {succeeded} out of {len(pdf_files)} files")
                print(f"Output saved to: {output_path}")
            else:
                print(f"Would process {len(pdf_files)} files")
        
        return 0 if succeeded == len(pdf_files) else 1

if __name__ == "__main__":
    sys.exit(main())