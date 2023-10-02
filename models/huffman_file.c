#include "hashtable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Huffman_file {
    unsigned char *buffer;
    int file_size;
    Hashtable *char_amounts;
} HFile;

// Função que lê os bytes do buffer e os insere na hashtable
void read_file_bytes(HFile *file) {
    int size = file->file_size;
    for (int i = 0; i < size; i++) {
        hash_insert(file->char_amounts, file->buffer[i]);
    }
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

    // Cria uma hashtable que recebe o byte atual e retorna a quantidade de
    // vezes que ele apareceu no arquivo
    tmp->char_amounts = create_hashtable(default_hash, 255);

    // Lê os bytes do arquivo e insere na hashtable
    read_file_bytes(tmp);
}
