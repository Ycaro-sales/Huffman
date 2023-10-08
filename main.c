#include "models/min_heap.h"
#include "utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// int main(int argc, char *argv[]) {
//     HFile *file = create_huffman_file("files/download.jpeg");
//
//     for (int i = 0; i < file->file_size; i++)
//         printf("%d\n", (unsigned int)file->buffer[i]);
//     return EXIT_SUCCESS;
// }
//

int main() {
    Heap *heap = create_heap(255);
    heap_enqueue(heap, 14, "14");
    heap_enqueue(heap, 18, "14");
    heap_enqueue(heap, 16, "14");
    heap_enqueue(heap, 16, "14");
    heap_enqueue(heap, 20, "14");
    heap_enqueue(heap, 17, "14");
    heap_enqueue(heap, 17, "14");
    heap_enqueue(heap, 23, "14");
    heap_print(heap);
    return 0;
}
