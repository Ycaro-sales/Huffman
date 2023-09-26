#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Huffman_file {
    char *buffer;
    int length;
} HFile;

HFile *create_hfile(char *file_name) {
    FILE *fileptr;
    long filelen;
    char *buffer;

    HFile *file = malloc(sizeof *file);

    fileptr = fopen(file_name, "rb");

    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);

    buffer = (char *)malloc(filelen * sizeof(char));
    fread(buffer, filelen, 1, fileptr);
    fclose(fileptr);

    file->buffer = buffer;
    file->length = filelen;

    return file;
}
