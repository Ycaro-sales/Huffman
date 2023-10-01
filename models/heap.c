#include "../utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1000

typedef struct heap {
    int items[HEAP_SIZE];
    int size;
    int capacity;
} heap;

heap *create_heap(int capacity) {
    heap *tmp = malloc(sizeof *tmp);
    tmp->size = 0;
    tmp->capacity = capacity;

    for (int i = 0; i < HEAP_SIZE; i++)
        tmp->items[i] = 0;

    return tmp;
}

int get_left_child_index(int parent_index) { return 2 * parent_index + 1; }
int get_right_child_index(int parent_index) { return 2 * parent_index + 2; }
int get_parent_index(int child_index) { return (child_index - 1) / 2; }

bool has_parent(heap *heap, int index) { return get_parent_index(index) >= 0; }

bool has_left_child(heap *heap, int index) {
    return get_left_child_index(index) < heap->size;
}

bool has_right_child(heap *heap, int index) {
    return get_right_child_index(index) < heap->size;
}

int left_child(heap *heap, int index) {
    return heap->items[get_left_child_index(index)];
}

int right_child(heap *heap, int index) {
    return heap->items[get_right_child_index(index)];
}

int peek(heap *heap) { return heap->items[0]; }

void heapify_up(heap *heap) {
    int index = heap->size - 1;
    while (has_parent(heap, index) &&
           get_parent_index(index) > heap->items[index]) {
        swap(&heap->items[get_parent_index(index)], &heap->items[index],
             sizeof(heap->items[0]));
        index = get_parent_index(index);
    }
}

void heapify_down(heap *heap) {
    int index = 0;

    while (has_left_child(heap, index)) {
        int smaller_child_index = get_left_child_index(index);

        if (has_right_child(heap, index) &&
            right_child(heap, index) < left_child(heap, index)) {
            smaller_child_index = get_right_child_index(index);
        }
        if (heap->items[index] < heap->items[smaller_child_index]) {
            break;
        } else {
            swap(&heap->items[index], &heap->items[smaller_child_index],
                 sizeof(heap->items[0]));
        }
        index = smaller_child_index;
    }
}

int pull(heap *heap) {
    int item = heap->items[0];
    heap->items[0] = heap->items[heap->size - 1];
    heap->size--;
    heapify_down(heap);
    return item;
}

void add(heap *heap, int item) {
    heap->items[heap->size] = item;
    heap->size++;
    heapify_up(heap);
}
