#include "huffman_file.h"
#include "../models/hashtable.h"
#include "../models/min_heap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Hashtable *read_file_bytes(HFile *file) {
    Hashtable *tmp = create_hash();
    int size = file->file_size;

    for (int i = 0; i < size; i++) {
        hash_add(tmp, file->buffer[i]);
    }

    return tmp;
}

HFile *create_huffman_file(char *file_name) {
    HFile *tmp = malloc(sizeof *tmp);
    FILE *stream;

    char *buffer;
    int file_length;

    // Lê o arquivo passado nos argumentos
    stream = fopen(file_name, "rb");

    // Busca o fim do arquivo
    fseek(stream, 0, SEEK_END);

    // Vê a posição atual do ponteiro dentro do arquivo e retorna a distancia do
    // começo do arquivo
    tmp->file_size = ftell(stream);

    // Aloca no buffer espaço suficiente para receber os bytes do arquivo
    tmp->buffer = (unsigned char *)malloc(file_length * sizeof(unsigned));

    // Lê o arquivo e passa os bytes para o buffer
    fread(buffer, file_length, 1, stream);

    // Fecha o arquivo
    fclose(stream);

    // Lê os bytes do arquivo e insere na hashtable
    read_file_bytes(tmp);
    tmp->char_frequency = read_file_bytes(tmp);

    return tmp;
}