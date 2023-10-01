#include "models/huffman_file.c"
#include "utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    HFile *file = create_hfile("files/download.jpeg");

    for (int i = 0; i < file->length; i++)
        printf("%d\n", (unsigned int)file->buffer[i]);
    return EXIT_SUCCESS;
}
