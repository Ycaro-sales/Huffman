#include "../models/min_heap.h"
#include "huffman_file.h"

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

typedef struct Huffman_tree {
    Heap *huffman_tree;
    int size;
} HTree;

typedef struct HuffNode {
    unsigned char data;
    int frequency;
    struct HuffNode *left;
    struct HuffNode *right;
} HuffNode;

HuffNode *create_huffman_node(unsigned char data, int frequency);
HTree *create_huffman_tree(HFile *file);

#endif // !HASHTABLE_H
