#include "../utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1000

typedef struct heap {
    int items[HEAP_SIZE];
    int size;
} Heap;

void heapify(Heap *heap, int size, int n) {
    int largest = n;
    int left = 2 * n + 1;
    int right = 2 * n + 2;

    if (left < heap->size && heap->items[left] < heap->items[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->items[right] < heap->items[largest]) {
        largest = right;
    }

    if (largest != n) {
        swap((void *)heap->items[n], (void *)heap->items[largest]);
    }
}