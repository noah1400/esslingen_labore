import pandas as pd
import math
number_of_rows = [300, 200, 800, 25, 100]

# DB2 Datatype sizes in bytes


def varchar_size(l): return l/2+2  # ???


smallint_size = 2
date_size = 4
decimal_size = 6
int_size = 4
timestamp_size = 10
char_size = 1
CLOB_size = 144  # descriptor size
BLOB_size = 144  # descriptor size

CLOB_actual_size = 1024000
BLOB_actual_size = 512000

full_row_size_books = varchar_size(50) + smallint_size*2
full_row_size_speaker = smallint_size+date_size+varchar_size(25)
full_row_size_stock = smallint_size+decimal_size+int_size
full_row_size_reorder = smallint_size+timestamp_size
full_row_size_author = smallint_size + \
    varchar_size(50)+char_size+CLOB_size+BLOB_size


books_avg_key_size = 2
speaker_avg_key_size = 0
stock_avg_key_size = 2
reorder_avg_key_size = 0
author_avg_key_size = 27 + 2  # ???


def calc_rows_per_page(ars: int) -> int:
    """
    Calculation of rows per page
    @param ars: average row size
    """
    rpp = math.floor(4028/(ars+10))  # 4028 / (average row size + 10)
    return rpp


def calc_number_of_pages(tnor: int, rpp: int) -> int:
    """
    Calculation of number of pages for a table
    @param tnor: total number of rows
    @param rpp: rows per page
    """
    return math.ceil((tnor/rpp)*1.1)  # total number of rows / rows per page * 1.1


def calc_index_size(aiks: int, nor: int) -> int:
    """
    Calculation of Index size
    @param aiks: average index key size
    @param nor: number of rows
    """
    return (aiks+9)*nor*2  # ( average index key size + 9 ) * number of rows * 2


def calc_lob_data_obj(lcs: int, norwld: int) -> float:
    """
    Calculation of LOB Data Object in bytes
    @param lcs: lob column sizes
    @param norwld: number of rows with lob data
    """
    return lcs*norwld*1.5  # LOB column sizes * number of rows with lob data * 1.5


def calc_alloc_obj(ldo: int) -> int:
    """
    Calculation of LOB Allocation Object in bytes
    @param ldo: lob data object
    """
    # ((LOB data object / 65,536,000,000)+(LOB data object / 8,192,000) * 4096)
    return (math.ceil(ldo/65536000000)+math.ceil(ldo/8192000)*4096)


books_ars = full_row_size_books  # average row size
books_rpp = calc_rows_per_page(books_ars)  # rows per page
books_nor = number_of_rows[0]  # number of rows
books_nop = calc_number_of_pages(books_nor, books_rpp)  # number of pages
books_is = calc_index_size(books_avg_key_size, books_nor)  # index size
books_lobs = 0  # LOB Size


speaker_ars = full_row_size_speaker
speaker_rpp = calc_rows_per_page(speaker_ars)
speaker_nor = number_of_rows[1]
speaker_nop = calc_number_of_pages(speaker_nor, speaker_rpp)
speaker_is = calc_index_size(speaker_avg_key_size, speaker_nor)
speaker_lobs = 0

stock_ars = full_row_size_stock
stock_rpp = calc_rows_per_page(stock_ars)
stock_nor = number_of_rows[2]
stock_nop = calc_number_of_pages(stock_nor, stock_rpp)
stock_is = calc_index_size(stock_avg_key_size, stock_nor)
stock_lobs = 0

reorder_ars = full_row_size_reorder
reorder_rpp = calc_rows_per_page(reorder_ars)
reorder_nor = number_of_rows[3]
reorder_nop = calc_number_of_pages(reorder_nor, reorder_rpp)
reorder_is = calc_index_size(reorder_avg_key_size, reorder_nor)
reorder_lobs = 0

author_ars = full_row_size_author
author_rpp = calc_rows_per_page(author_ars)
author_nor = number_of_rows[4]
author_nop = calc_number_of_pages(author_nor, author_rpp)
author_is = calc_index_size(author_avg_key_size, author_nor)
author_lobs = calc_lob_data_obj(CLOB_actual_size+BLOB_actual_size, author_nor)
author_alloc_obj = calc_alloc_obj(author_lobs)


"""
Dataframe

Table Name      Number of Rows per Page     Table Pages     Index Size (bytes)    LOB Size (bytes)   Alloc Obj (bytes)
BOOKS
SPEAKER
STOCK
REORDER
AUTHOR
"""


data = {
    'Table Name': ['BOOKS', 'SPEAKER', 'STOCK', 'REORDER', 'AUTHOR'],
    'Number of Rows per Page': [books_rpp, speaker_rpp, stock_rpp, reorder_rpp, author_rpp],
    'Table Pages': [books_nop, speaker_nop, stock_nop, reorder_nop, author_nop],
    'Index Size (bytes)': [books_is, speaker_is, stock_is, reorder_is, author_is],
    'LOB Size (bytes)': [0, 0, 0, 0, author_alloc_obj+author_lobs]
}
df = pd.DataFrame(data)
print(df)

# dataframe to csv
df.to_csv('partA.csv', index=False)
# convert to excel
# https://convertio.co/de/csv-xlsx/

"""
Dataframe

Table Space Name    Container Location      Number of pages in each container   Extent Size (number of pages)
DMS01               C:\dms\dms01.data                                           4
DMS02               C:\dms\dms02.data                                           2
DMS03               C:\dms\dms03.data                                           8
DMS04               C:\dms\dms04.data                                           2
DMS05               C:\dms\dms05.data                                           2
DMS06               C:\dms\dms06.data                                           4
SMS01               C:\sms\sms01,C:\sms\sms02                                   4
"""


"""
Calculate the number of pages in each container

Using first table in Part B as lookup for the correct numbers
"""

DMS01_number_of_extents = math.ceil(3+number_of_rows[4]+(author_nop/4))
DMS02_number_of_extents = math.ceil(3+number_of_rows[4]+number_of_rows[2]+(author_nop/2)+(stock_nop/2))
DMS03_number_of_extents = math.ceil(3+number_of_rows[4]+(author_nop/8))
DMS04_number_of_extents = math.ceil(3+number_of_rows[0]+number_of_rows[1]+(books_nop/2)+(speaker_nop/2))
DMS05_number_of_extents = math.ceil(3+number_of_rows[0]+(books_nop/2))
DMS06_number_of_extents = math.ceil(3+number_of_rows[2]+(stock_nop/4))
SMS01_number_of_extents = math.ceil(3+number_of_rows[3]+(reorder_nop/4))

"""
Number of extents times extent size
"""

DMS01_number_of_pages_in_each_container = 4*DMS01_number_of_extents
DMS02_number_of_pages_in_each_container = 2*DMS02_number_of_extents
DMS03_number_of_pages_in_each_container = 8*DMS03_number_of_extents
DMS04_number_of_pages_in_each_container = 2*DMS04_number_of_extents
DMS05_number_of_pages_in_each_container = 2*DMS05_number_of_extents
DMS06_number_of_pages_in_each_container = 4*DMS06_number_of_extents
SMS01_number_of_pages_in_each_container = 4*SMS01_number_of_extents


df = pd.DataFrame({
    'Table Space Name': ['DMS01', 'DMS02', 'DMS03', 'DMS04', 'DMS05', 'DMS06', 'SMS01'],
    'Container Location': ['C:\dms\dms01.data', 'C:\dms\dms02.data', 'C:\dms\dms03.data', 'C:\dms\dms04.data', 'C:\dms\dms05.data', 'C:\dms\dms06.data', 'C:\sms\sms01,C:\sms\sms02'],
    'Number of pages in each container': [DMS01_number_of_pages_in_each_container, DMS02_number_of_pages_in_each_container, DMS03_number_of_pages_in_each_container, DMS04_number_of_pages_in_each_container, DMS05_number_of_pages_in_each_container, DMS06_number_of_pages_in_each_container, SMS01_number_of_pages_in_each_container],
    'Extent Size (number of pages)': [4, 2, 8, 2, 2, 4, 4]
})
print(df)

# dataframe to csv
df.to_csv('partB.csv', index=False)