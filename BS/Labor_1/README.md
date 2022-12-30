# `sortmusic.sh`
This script allows you to sort a collection of MP3 files based on various criteria.
### Usage
To use the script, first make sure it is executable by running `chmod +x sortmusic.sh`. Then, you use one of the four parameter:

- `-y` or `--year` sorts the MP3 files by the year they were released, as indicated by the year tag in the metadata.
- `-a` or `--artist` sorts the MP3 files by the artist's name, as indicated by the artist tag in the metadata.
- `-d` or `--disc` sorts the MP3 files by the album they belong to, as indicated by the album tag in the metadata.
- `-h` or `--help` displays a help message

For example, to sort the MP3 files by year, you can run `./sortmusic.sh -y`. The sorted MP3 files will be placed in a directory called "sorted".

#### Requirements
This script requires the `id3v2` command, which is part of the `id3lib-tools` package. Make sure this package is installed on your system before using the script.

### Note
**Please note that this script is intended to be used as a reference and not copied verbatim.**