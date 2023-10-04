#include "tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Huffman_tree {
    Tree *tree;
    int size;
} HTree;

HTree *create_huffman_tree(HFile *file) {}
