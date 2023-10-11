#include "huffman_tree.h"
#include "../models/hashtable.h"
#include "../models/max_heap.h"
#include "../utils.h"
#include "huffman_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UNSIGNED_CHAR_CAPACITY 255

HuffNode *create_huffman_node(unsigned char data, int frequency) {
        HuffNode *tmp = malloc(sizeof *tmp);

        tmp->data = data;
        tmp->frequency = frequency;
        tmp->next = NULL;
        tmp->left = NULL;
        tmp->right = NULL;

        return tmp;
}

void fill_heap_with_char_frequency(Heap *heap, Hashtable *char_frequency) {
        int size = ARRAY_SIZE(char_frequency->array);

        for (int i = 0; i < size; i++) {
                if (hash_search(char_frequency, i)) {
                        HuffNode *tmp =
                            create_huffman_node(i, hash_get(char_frequency, i));

                        heap_enqueue(heap, hash_get(char_frequency, i), tmp);
                }
        }
}

HuffNode *merge_huffnodes(HuffNode *left, HuffNode *right) {
        HuffNode *tmp = malloc(sizeof *tmp);

        tmp->data = '*';
        tmp->frequency = left->frequency + right->frequency;

        tmp->left = left;
        tmp->right = right;

        return tmp;
}

HTree *heap_to_hufflist(Heap *heap) {
        HTree *tmp = malloc(sizeof *tmp);
        tmp->root = (HuffNode *)heap->items[0]->data;

        HuffNode *tmpNode = tmp->root;

        for (int i = 1; i < heap->size; i++) {
                tmpNode->next = (HuffNode *)heap->items[i]->data;
                tmpNode = tmpNode->next;
        }

        return tmp;
}

void htree_insert_sorted(HTree *htree, HuffNode *hnode) {
        HuffNode *curr = htree->root;

        if (hnode->frequency < htree->root->frequency) {
                hnode->next = htree->root;
                htree->root = hnode;
                return;
        }

        while (curr->next->next) {
                if (hnode->frequency <= curr->next->next->frequency) {
                        hnode->next = curr->next;
                        curr->next = hnode;
                        return;
                }

                curr = curr->next;
        }

        curr->next = hnode;
}

HuffNode *pop_htree(HTree *htree) {
        HuffNode *tmp = htree->root;

        htree->root = htree->root->next;
        tmp->next = NULL;

        return tmp;
}

HTree *hufflist_to_hufftree(HTree *htree) {
        HuffNode *curr = htree->root;

        while (htree->root->next != NULL) {
                HuffNode *tmpLeft = pop_htree(htree);
                HuffNode *tmpRight = pop_htree(htree);
                HuffNode *mergedNode = merge_huffnodes(tmpLeft, tmpRight);

                htree_insert_sorted(htree, mergedNode);
        }

        return htree;
}

bool is_leaf(HuffNode *hnode) {
        return (hnode->left == NULL && hnode->right == NULL);
}

HTree *create_huffman_tree(HFile *file) {
        HTree *tmp = malloc(sizeof *tmp);

        Heap *heap = create_heap(UNSIGNED_CHAR_CAPACITY);

        fill_heap_with_char_frequency(heap, file->char_frequency);

        heap_sort(heap);

        tmp = heap_to_hufflist(heap);

        tmp = hufflist_to_hufftree(tmp);

        return tmp;
}
