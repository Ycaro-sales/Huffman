#include "huffman_tree.h"
#include "../models/hashtable.h"
#include "../models/min_heap.h"
#include "huffman_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UNSIGNED_CHAR_CAPACITY 255

HuffNode *create_huffman_node(unsigned char data, int frequency) {
    HuffNode *tmp = malloc(sizeof *tmp);

    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

void fill_heap_with_char_frequency(Heap *heap, Hashtable *char_frequency) {
    for (int i = 0; i < UNSIGNED_CHAR_CAPACITY; i++) {
        if (char_frequency->array[i] > 0) {
            HuffNode *tmp = create_huffman_node(i, char_frequency->array[i]);
            heap_add(heap, char_frequency->array[i], tmp);
        }
    }
}

HTree *create_huffman_tree(HFile *file) {
    HTree *tmp = malloc(sizeof *tmp);

    Heap *tmpheap = create_heap(UNSIGNED_CHAR_CAPACITY);

    fill_heap_with_char_frequency(tmpheap, file->char_frequency);
    heap_sort(tmpheap);

    return tmp;
}
