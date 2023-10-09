#include "core/huffman_file.h"
#include "core/huffman_tree.h"
#include "models/min_heap.h"
#include "utils.h"
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
        HFile *file = create_huffman_file("./files/file.txt");

        HTree *huffTree = create_huffman_tree(file);

        heap_print(huffTree->tree);

        return 0;
}
