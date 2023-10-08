#ifndef MINHEAP_H
#define MINHEAP_H

#define HEAP_SIZE 1000

typedef struct heap_node {
    int num;
    void *data;
} HeapNode;

typedef struct heap {
    HeapNode *items[HEAP_SIZE];
    int size;
    int capacity;
} Heap;

Heap *create_heap(int capacity);
HeapNode *heap_pull(Heap *heap);

void heap_add(Heap *heap, int num, void *data);
void heap_sort(Heap *heap);

#endif // !HASHTABLE_H
