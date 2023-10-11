#include <stdio.h>

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

typedef struct decompressed_file {
        char *file_name;
        unsigned char *buffer;
        FILE *decompressed_file_pointer;
} DecompressedFile;

void decompress(char *file_name);

#endif // !COMPRESS_H
