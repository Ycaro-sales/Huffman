#ifndef MINHEAP_H
#define MINHEAP_H

#define HEAP_SIZE 1000

typedef struct HeapNode {
    int num;
    void *data;
} HeapNode;

typedef struct heap {
    HeapNode *items[HEAP_SIZE];
    int size;
    int capacity;
} Heap;

Heap *create_heap(int capacity);
int *heap_pull(Heap *heap);

void heap_enqueue(Heap *heap, int num, void *data);
void heap_dequeue(Heap *heap);
void heap_print(Heap *heap);

#endif // !HASHTABLE_H
