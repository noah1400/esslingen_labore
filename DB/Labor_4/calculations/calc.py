number_of_rows = [300, 200, 8000, 25, 100]

# DB2 Datatype sizes in bytes
varchar_size = lambda l: l/2
smallint_size = 2
date_size = 4
decimal_size = 6
int_size = 4
timestamp_size = 10
char_size = 1
CLOB_size = 144 # descriptor to file of 1024000 bytes
BLOB_size = 144 # descriptor to file of 512000 bytes

CLOB_actual_size = 1024000
BLOB_actual_size = 512000

full_row_size_books = varchar_size(50) + smallint_size*2
full_row_size_speaker = smallint_size+date_size+varchar_size(25)
full_row_size_stock = smallint_size+decimal_size+int_size
full_row_size_reorder = smallint_size+timestamp_size
full_row_size_author = smallint_size+varchar_size(50)+char_size+CLOB_size+BLOB_size

avg_row_size = lambda l: l
avg_index_key_size = 1

import math

def calc_rows_per_page(ars): # average row size
    return math.floor(4096/(ars+10))

def calc_number_of_pages(tnor, rpp): # total number of rows, rows per page
    return math.ceil((tnor/rpp)*1.1)

def calc_index_size(aiks, nor): # average index key size, number of rows
    return (aiks+9)*nor*2

def calc_lob_data_obj(lcs, norwld): # lob column size, number of rows with lob data
    return lcs*norwld*1.5

def calc_alloc_obj(ldo): # lob data object
    return (math.ceil(ldo/65536000000)+math.ceil(ldo/8192000)*4096)

books_ars = avg_row_size(full_row_size_books) # average row size
books_rpp = calc_rows_per_page(books_ars) # rows per page
books_nor = number_of_rows[0] # number of rows
books_nop = calc_number_of_pages(books_nor, books_rpp) # number of pages
books_is = calc_index_size(avg_index_key_size, books_nor) # index size
books_norwld = 0 # number of rows with lob data


speaker_ars = avg_row_size(full_row_size_speaker)
speaker_rpp = calc_rows_per_page(speaker_ars)
speaker_nor = number_of_rows[1]
speaker_nop = calc_number_of_pages(speaker_nor, speaker_rpp)
speaker_is = calc_index_size(avg_index_key_size, speaker_nor)

stock_ars = avg_row_size(full_row_size_stock)
stock_rpp = calc_rows_per_page(stock_ars)
stock_nor = number_of_rows[2]
stock_nop = calc_number_of_pages(stock_nor, stock_rpp)
stock_is = calc_index_size(avg_index_key_size, stock_nor)

reorder_ars = avg_row_size(full_row_size_reorder)
reorder_rpp = calc_rows_per_page(reorder_ars)
reorder_nor = number_of_rows[3]
reorder_nop = calc_number_of_pages(reorder_nor, reorder_rpp)
reorder_is = calc_index_size(avg_index_key_size, reorder_nor)

author_ars = avg_row_size(full_row_size_author)
author_rpp = calc_rows_per_page(author_ars)
author_nor = number_of_rows[4]
author_nop = calc_number_of_pages(author_nor, author_rpp)
author_is = calc_index_size(avg_index_key_size, author_nor)



"""
Dataframe

Table Name      Number of Rows per Page     Table Pages     Index Size (bytes)
BOOKS
SPEAKER
STOCK
REORDER
AUTHOR
"""

import pandas as pd

data = {
    'Table Name': ['BOOKS', 'SPEAKER', 'STOCK', 'REORDER', 'AUTHOR'],
    'Number of Rows per Page': [books_rpp, speaker_rpp, stock_rpp, reorder_rpp, author_rpp],
    'Table Pages': [books_nop, speaker_nop, stock_nop, reorder_nop, author_nop],
    'Index Size (bytes)': [books_is, speaker_is, stock_is, reorder_is, author_is]
}
df = pd.DataFrame(data)
print(df)