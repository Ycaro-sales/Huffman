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

typedef struct Huffman_tree {
        HuffNode *root;
        int size;
} HTree;

HuffNode *create_huffman_node(unsigned char data, int frequency);
bool is_leaf(HuffNode *hnode);
HTree *create_huffman_tree(HFile *file);

#endif // !HASHTABLE_H
