#include "../models/hashtable.h"

#ifndef HUFFMANFILE_H
#define HUFFMANFILE_H

typedef struct huffman_file {
        unsigned char *buffer;
        char *name;
        unsigned int file_size;
        Hashtable *char_frequency;
} HFile;

HFile *create_huffman_file(char *file_name);
Hashtable *read_file_bytes(HFile *file);

#endif // !HUFFMANFILE_H
