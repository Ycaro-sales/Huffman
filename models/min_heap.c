#include "./min_heap.h"
#include "../utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Heap *create_heap(int capacity) {
    Heap *tmp = malloc(sizeof *tmp);
    tmp->size = 0;
    tmp->capacity = capacity;

    for (int i = 0; i < HEAP_SIZE; i++)
        tmp->items[i] = 0;

    return tmp;
}

int get_left_child_index(int parent_index) { return 2 * parent_index + 1; }
int get_right_child_index(int parent_index) { return 2 * parent_index + 2; }
int get_parent_index(int child_index) { return (child_index - 1) / 2; }

bool has_parent(Heap *heap, int index) { return get_parent_index(index) >= 0; }

bool has_left_child(Heap *heap, int index) {
    return get_left_child_index(index) < heap->size;
}

bool has_right_child(Heap *heap, int index) {
    return get_right_child_index(index) < heap->size;
}

int left_child(Heap *heap, int index) {
    return heap->items[get_left_child_index(index)]->num;
}

int right_child(Heap *heap, int index) {
    return heap->items[get_right_child_index(index)]->num;
}

int heap_peek(Heap *heap) { return heap->items[0]->num; }

void heapify_up(Heap *heap) {
    int index = heap->size - 1;
    while (has_parent(heap, index) &&
           get_parent_index(index) > heap->items[index]->num) {
        swap(&heap->items[get_parent_index(index)]->num,
             &heap->items[index]->num, sizeof(heap->items[0]->num));
        index = get_parent_index(index);
    }
}

void heapify_down(Heap *heap) {
    int index = 0;

    while (has_left_child(heap, index)) {
        int smaller_child_index = get_left_child_index(index);

        if (has_right_child(heap, index) &&
            right_child(heap, index) < left_child(heap, index)) {
            smaller_child_index = get_right_child_index(index);
        }
        if (heap->items[index]->num < heap->items[smaller_child_index]->num) {
            break;
        } else {
            swap(&heap->items[index], &heap->items[smaller_child_index],
                 sizeof(heap->items[0]->num));
        }
        index = smaller_child_index;
    }
}

HeapNode *heap_pull(Heap *heap) {
    HeapNode *item = heap->items[0];
    heap->items[0] = heap->items[heap->size - 1];
    heap->size--;
    heapify_down(heap);
    return item;
}

void heap_add(Heap *heap, int num, void *data) {
    HeapNode *tmp = malloc(sizeof *tmp);

    tmp->num = num;
    tmp->data = data;

    heap->items[heap->size] = tmp;
    heap->size++;

    heapify_up(heap);
}

void heap_sort(Heap *heap) {}
