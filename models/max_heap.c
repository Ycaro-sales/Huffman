#include "./max_heap.h"
#include "../utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Heap *create_heap(int capacity) {
        Heap *tmp = malloc(sizeof *tmp);
        tmp->size = 0;
        tmp->capacity = capacity;

        for (int i = 0; i < HEAP_SIZE; i++)
                tmp->items[i] = NULL;

        return tmp;
}

int get_left_index(int parent_index) { return 2 * parent_index + 1; }
int get_right_index(int parent_index) { return 2 * parent_index + 2; }
int get_parent_index(int child_index) { return (child_index - 1) / 2; }

bool has_parent(Heap *heap, int index) { return get_parent_index(index) >= 0; }

bool has_left_child(Heap *heap, int index) {
        return get_left_index(index) < heap->size;
}

bool has_right_child(Heap *heap, int index) {
        return get_right_index(index) < heap->size;
}

int left_child(Heap *heap, int index) {
        return heap->items[get_left_index(index)]->num;
}

int right_child(Heap *heap, int index) {
        return heap->items[get_right_index(index)]->num;
}

int heap_peek(Heap *heap) { return heap->items[0]->num; }

int item_of_heap(Heap *heap, int i) { return heap->items[i]->num; }

bool is_empty(Heap *heap) { return heap->size == 0; }

void max_heapify(Heap *heap, int i) {
        int largest;
        int left_index = get_left_index(i);
        int right_index = get_right_index(i);

        if (left_index <= heap->size - 1 &&
            heap->items[left_index]->num > heap->items[i]->num) {
                largest = left_index;
        } else {
                largest = i;
        }

        if (right_index <= heap->size - 1 &&
            heap->items[right_index]->num > heap->items[largest]->num) {
                largest = right_index;
        }

        if (heap->items[i] != heap->items[largest]) {
                SWAP(heap->items[i], heap->items[largest]);
                max_heapify(heap, largest);
        }
}

HeapNode *heap_dequeue(Heap *heap) {
        if (is_empty(heap)) {
                printf("Heap Underflow");
                return NULL;
        } else {
                HeapNode *item = heap->items[0];

                heap->items[0] = heap->items[heap->size - 1];
                heap->size--;

                max_heapify(heap, 0);

                return item;
        }
}

void heap_enqueue(Heap *heap, int num, void *data) {
        if (heap->size >= HEAP_SIZE) {
                printf("Heap Overflow");
        } else {
                HeapNode *tmp = malloc(sizeof *tmp);

                tmp->num = num;
                tmp->data = data;

                heap->items[heap->size++] = tmp;

                int key_index = heap->size - 1;
                int parent_index = get_parent_index(heap->size - 1);

                while (parent_index >= 0 &&
                       heap->items[key_index]->num >
                           heap->items[parent_index]->num) {
                        SWAP(heap->items[key_index], heap->items[parent_index]);
                        key_index = parent_index;
                        parent_index = get_parent_index(key_index);
                }
        }
}

void heap_sort(Heap *heap) {
        int size = heap->size;

        for (int i = heap->size - 1; i >= 1; i--) {
                SWAP(heap->items[0], heap->items[i]);
                heap->size--;
                max_heapify(heap, 0);
        }

        heap->size = size;
}

void heap_print(Heap *heap) {
        for (int i = 0; i < heap->size; i++) {
                printf("heap index %d: %d\n", i, heap->items[i]->num);
        }
}
