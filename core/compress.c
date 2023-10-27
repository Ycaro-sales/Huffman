#include "compress.h"
#include "../models/hashtable.h"
#include "../utils.h"
#include "huffman_file.h"
#include "huffman_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função que escreve a arvore de huffman no cabeçalho do arquivo compactado
 * @param compressed_file: arquivo compactado
 * @param huffman_tree: arvore de huffman
 * @return arquivo compactado
 */
FILE *write_huffman_tree_bytes_to_header(FILE *compressed_file,
                                         HTree *huffman_tree) {
        for (int i = 0; i < huffman_tree->stringfied_tree_size; i++) {
                putc(huffman_tree->stringfied_tree[i], compressed_file);
        }
        return compressed_file;
}

/* Função que calcula o tamanho do lixo
 * @param compressed_hash: Hash com os caminhos de cada caracter
 * @param file: arquivo a ser compactado
 */
int calculate_thrash_size(CompressedHash *compressed_hash, HFile *file) {
        int thrash_size = 0;
        for (unsigned int i = 0; i < 256; i++) {
                if (compressed_hash->paths[i] > 0) {
                        int path_size = strlen(compressed_hash->paths[i]);
                        thrash_size +=
                            path_size * file->char_frequency->array[i];
                }
        }
        return thrash_size % 8;
}

/* Função que escreve o lixo e o tamanho da arvore de huffman no cabeçalho do
 * @param compressed_file: arquivo Compactado
 * @param thrash: tamanho do lixo
 * @param tree_size: tamanho da arvore de huffman_tree
 * @return arquivo compactado
 */
FILE *write_thrash_and_tree_size_to_header(FILE *compressed_file,
                                           unsigned char thrash,
                                           int tree_size) {
        tree_size = tree_size << 5;
        tree_size = tree_size | thrash;

        printf("%d\n", compressed_file == NULL);
        fputc(tree_size, compressed_file);

        return compressed_file;
}
/* Função que escreve o cabeçalho no arquivo Compactado
 * @param file: arquivo a ser compactado
 * @param compressed_file: arquivo compactado
 * @param huffman_tree: arvore de huffman
 * @param compressed_hash: Hash com os caminhos de cada caracter
 * @return arquivo compactado
 */

FILE *write_header_to_file(HFile *file, FILE *compressed_file,
                           HTree *huffman_tree,
                           CompressedHash *compressed_hash) {
        printf("Calculando Tamanho do lixo\n");
        int thrash_size = calculate_thrash_size(compressed_hash, file);
        unsigned char thrash = thrash_size << 5;

        printf("%d\n", compressed_file == NULL);
        printf("Escrevendo cabeçalho\n");
        compressed_file = write_thrash_and_tree_size_to_header(
            compressed_file, thrash, huffman_tree->stringfied_tree_size);

        printf("Escrevendo arvore de huffman no cabeçalho\n");
        compressed_file =
            write_huffman_tree_bytes_to_header(compressed_file, huffman_tree);

        return compressed_file;
}

/* Função que escreve os bits no arquivo compactado
 * @param file: arquivo a ser Compactado
 * @param compressed_file: arquivo Compactado
 * @param compressed_hash: Hash com os caminhos de cada caracter
 * @return arquivo compactado
 */
FILE *write_bits_to_file(HFile *file, FILE *compressed_file,
                         CompressedHash *compressed_hash) {
        int bit_count = 7;
        unsigned char current_byte = 0;

        for (unsigned int i = 0; i < file->file_size; i++) {
                char *path = compressed_hash->paths[file->buffer[i]];
                for (int j = 0; j < strlen(path); j++) {
                        if (path[j] == '1') {
                                set_bit(current_byte, bit_count);
                        }

                        bit_count--;

                        if (bit_count == 0) {
                                bit_count = 7;
                        }
                }
        }

        return compressed_file;
}

/* Função que compacta o arquivo e cria o arquivo compactado
 * @param file_name: nome do arquivo a ser compactado
 */
void compress(char *file_name) {
        printf("iniciando compressão!\n");
        printf("criando arquivo huffman...\n");
        HFile *file = create_huffman_file(file_name);
        FILE *compressed_file;
        char compressed_file_name[10000];

        printf("Deseja Escolher o nome do arquivo compactado? (s/n)\n");
        char option;
        scanf("%c", &option);

        if (option == 's') {
                printf("Digite o nome do arquivo compactado:\n");
                scanf("%s", compressed_file_name);
                compressed_file =
                    fopen(strcat(compressed_file_name, ".huff"), "w");
        } else {
                compressed_file = fopen("file.huff", "w");
        }

        if (compressed_file == NULL) {
                printf("algo deu errado na abertura do arquivo!\n");
                return;
        }

        printf("Criando arvore de huffman...\n");
        HTree *huffman_tree = create_huffman_tree(file);

        // printf("abrindo arquivo...\n");
        // compressed_file = fopen(compressed_file_name, "wb");

        printf("%d\n", compressed_file == NULL);
        printf("Criando cabeçalho...\n");
        compressed_file = write_header_to_file(
            file, compressed_file, huffman_tree, huffman_tree->compressed_hash);
        printf("Escrevendo Bits...\n");
        compressed_file = write_bits_to_file(file, compressed_file,
                                             huffman_tree->compressed_hash);

        fclose(compressed_file);

        printf("%s Compactado com Successo!!\nArquivo compactado: %s\n\n",
               file_name, compressed_file_name);
}
