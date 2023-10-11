#include "../utils.h"
#include <stdio.h>

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

typedef struct decompressed_file {
        char *file_name;
        unsigned char *buffer;
        FILE *decompressed_file_pointer;
} DecompressedFile;

typedef struct header {
        unsigned char *stringfied_tree;
        int stringfied_tree_size;
        int thrash;
} Header;

void decompress(char *file_name);

#endif // !COMPRESS_H
