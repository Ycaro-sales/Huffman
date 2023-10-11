#include "huffman_tree.h"
#include "../models/hashtable.h"
#include "../models/max_heap.h"
#include "../utils.h"
#include "huffman_file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define UNSIGNED_CHAR_CAPACITY 255
#define SLASH 92

HuffNode *create_huffman_node(unsigned char data, int frequency) {
        HuffNode *tmp = malloc(sizeof *tmp);

        tmp->data = data;
        tmp->frequency = frequency;
        tmp->next = NULL;
        tmp->left = NULL;
        tmp->right = NULL;

        return tmp;
}

// create a function thats reads a string from a pre-order tree and return a
// huffman tree in c

HTree *string_to_huffmantree(unsigned char *stringfied_tree, int size) {
        HTree *tmp = malloc(sizeof *tmp);
        tmp->root = create_huffman_node(stringfied_tree[0], 0);

        HuffNode *curr = tmp->root;

        for (int i = 1; i < size; i++) {
                HuffNode *tmpLeft = NULL;
                HuffNode *tmpRight = NULL;

                if (stringfied_tree[i] == SLASH) {

                        tmpLeft =
                            create_huffman_node(stringfied_tree[i + 1], 0);
                        tmpRight =
                            create_huffman_node(stringfied_tree[i + 2], 0);
                        hnode_insert_children(curr, tmpLeft, tmpRight);

                        i += 2;
                } else {
                        curr->left = create_huffman_node(stringfied_tree[i], 0);
                        curr->right =
                            create_huffman_node(stringfied_tree[i + 1], 0);
                        i++;
                }

                curr = curr->left;
        }

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

HuffNode *hnode_insert_children(HuffNode *parent, HuffNode *left,
                                HuffNode *right) {
        parent->left = left;
        parent->right = right;

        return parent;
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
        while (htree->root->next != NULL) {
                HuffNode *tmpLeft = pop_htree(htree);
                HuffNode *tmpRight = pop_htree(htree);
                HuffNode *mergedNode = merge_huffnodes(tmpLeft, tmpRight);

                htree_insert_sorted(htree, mergedNode);
        }

        return htree;
}

/* Função recursiva que transforma a arvore de huffman em uma stringfied_tree
 * @param node: nó da arvore de huffman
 * @param tree_string: string de buffer
 * @param i: indice da stringfied_tree
 */
void tree_to_string(HuffNode *node, unsigned char *tree_string, int i) {
        if (is_leaf(node) && (node->data == '*' || node->data == SLASH)) {
                tree_string[i++] = SLASH;
                tree_string[i++] = node->data;
                return;
        }

        tree_string[i++] = node->data;
        tree_to_string(node->left, tree_string, i);
        tree_to_string(node->right, tree_string, i);
}

unsigned char *Huffman_tree_to_string(HTree *huffman_tree) {
        unsigned char *tree_string = malloc(sizeof(unsigned char) * 256);
        int i = 0;
        tree_to_string(huffman_tree->root, tree_string, i);
        return tree_string;
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

        tmp->stringfied_tree = Huffman_tree_to_string(tmp);
        tmp->stringfied_tree_size =
            sizeof(tmp->stringfied_tree) - sizeof(unsigned char);

        return tmp;
}
