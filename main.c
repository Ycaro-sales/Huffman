#include "core/huffman_file.h"
#include "core/huffman_tree.h"
#include "models/max_heap.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        HFile *file = create_huffman_file("./files/file.txt");

        HTree *HTree = create_huffman_tree(file);

        heap_print(HTree->tree);

        return EXIT_SUCCESS;
}
