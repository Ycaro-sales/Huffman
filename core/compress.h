#include "../models/hashtable.h"

#ifndef COMPRESS_H
#define COMPRESS_H

typedef struct CompressedHashTable {
        char *paths[255];
        int thrash_size;
} CompressedHash;

void compress(char *file_name);

#endif // !COMPRESS_H
