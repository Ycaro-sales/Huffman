#include "models/working_file.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    HFile *file = create_hfile("files/download.jpeg");

    for (int i = 0; i < file->length; i++)
        printf("%c\n", file->buffer[i]);
    return EXIT_SUCCESS;
}
