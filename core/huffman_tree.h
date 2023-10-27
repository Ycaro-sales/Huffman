#include "../models/max_heap.h"
#include "huffman_file.h"

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

typedef struct HuffNode {
        unsigned char data;
        int frequency;
        struct HuffNode *next;
        struct HuffNode *left;
        struct HuffNode *right;
} HuffNode;

typedef struct CompressedHashTable {
        char *paths[255];
        int thrash_size;
} CompressedHash;

typedef struct Huffman_tree {
        HuffNode *root;
        CompressedHash *compressed_hash;
        unsigned char *stringfied_tree;
        int stringfied_tree_size;
} HTree;

HuffNode *create_huffman_node(unsigned char data, int frequency);
HuffNode *hnode_insert_children(HuffNode *parent, HuffNode *left,
                                HuffNode *right);

HTree *create_huffman_tree(HFile *file);
HTree *string_to_huffmantree(unsigned char *stringfied_tree, int size);

bool is_leaf(HuffNode *hnode);

#endif // !HASHTABLE_H
