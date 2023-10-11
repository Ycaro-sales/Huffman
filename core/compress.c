#include "compress.h"
#include "../models/hashtable.h"
#include "../utils.h"
#include "huffman_file.h"
#include "huffman_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fill_compressed_hash(HuffNode *root, CompressedHash *compressed_hash,
                          char *path) {
        if (is_leaf(root)) {
                compressed_hash->paths[root->data] = path;
        } else {
                char *tmpRight;
                char *tmpLeft;

                strncpy(tmpRight, path, sizeof(path) + sizeof(char));
                strncpy(tmpLeft, path, sizeof(path) + sizeof(char));

                fill_compressed_hash(root->left, compressed_hash,
                                     strcat(tmpLeft, "0"));
                fill_compressed_hash(root->right, compressed_hash,
                                     strcat(tmpRight, "1"));
        }
}

CompressedHash *create_compressed_hash(HTree *htree) {
        CompressedHash *tmp = malloc(sizeof *tmp);

        char *path = "";

        fill_compressed_hash(htree->root, tmp, path);
        // tmp->thrash;

        return tmp;
}

// TODO
FILE *write_thrash_to_header(FILE *compressed_file, int thrash_size) {
        return compressed_file;
}

// TODO
FILE *write_huffman_tree_bytes_to_header(FILE *compressed_file,
                                         HTree *Huffman_tree) {
        return compressed_file;
}

FILE *write_header_to_file(HFile *file, FILE *compressed_file,
                           HTree *huffman_tree,
                           CompressedHash *compressed_hash) {
        int thrash_size;
        compressed_file = write_thrash_to_header(compressed_file, thrash_size);
        compressed_file =
            write_huffman_tree_bytes_to_header(compressed_file, huffman_tree);
        return compressed_file;
}

// TODO
FILE *write_bits_to_file(unsigned char *buffer, FILE *compressed_file,
                         CompressedHash *compressed_hash) {
        int byte_count;
        return compressed_file;
}

void compress(char *file_name) {

        HFile *file = create_huffman_file(file_name);
        char *compressed_file_name = strcat(file->name, ".huff");

        FILE *compressed_file;

        HTree *huffman_tree = create_huffman_tree(file);
        CompressedHash *compressed_hash = create_compressed_hash(huffman_tree);

        fopen(compressed_file_name, "wb");

        compressed_file = write_header_to_file(file, compressed_file,
                                               huffman_tree, compressed_hash);
        compressed_file =
            write_bits_to_file(file->buffer, compressed_file, compressed_hash);

        printf("%s Compactado com Successo!!\nArquivo compactado: %s\n\n",
               file_name, compressed_file_name);
}
