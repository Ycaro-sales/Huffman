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
        ListNode *curr = char_frequency->used_indexes->head;

        while (curr->next != NULL) {
                int i = *((int *)(curr->data));

                if (char_frequency->array[i] > 0 &&
                    hash_get(char_frequency, i) > 0) {
                        HuffNode *tmp =
                            create_huffman_node(i, hash_get(char_frequency, i));
                        heap_enqueue(heap, char_frequency->array[i], tmp);
                }
                curr = curr->next;
        }
}

HTree *create_huffman_tree(HFile *file) {
        HTree *tmp = malloc(sizeof *tmp);

        Heap *tmpheap = create_heap(UNSIGNED_CHAR_CAPACITY);

        fill_heap_with_char_frequency(tmpheap, file->char_frequency);
        heap_sort(tmpheap);

        return tmp;
}
