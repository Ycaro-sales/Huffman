#include "huffman_tree.h"
#include "../models/hashtable.h"
#include "../models/min_heap.h"
#include "huffman_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

HuffNode *create_huffman_node(unsigned char data, int frequency) {
    HuffNode *tmp = malloc(sizeof *tmp);

    tmp->data = data;
    tmp->frequency = frequency;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

void fill_huffman_heap(Heap *huffman_tree, Hashtable *char_frequency) {
    ListNode *curr = char_frequency->used_indexes->head;
    HuffNode *tmp = NULL;
    while (curr->next != NULL) {
        tmp = create_huffman_node(curr->data);
        heap_add(huffman_tree, );
        curr = curr->next;
    }
}

HTree *create_huffman_tree(HFile *file) {
    HTree *tmp = malloc(sizeof *tmp);
    tmp->huffman_tree = create_heap(sizeof *tmp);

    return tmp;
}
