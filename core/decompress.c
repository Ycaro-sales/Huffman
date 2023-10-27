#include "decompress.h"
#include "../utils.h"
#include "huffman_file.h"
#include "huffman_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLASH 92

Header *get_header_from_compressed_file(HFile *file) {
        Header *header = malloc(sizeof *header);
        int tmp = 0;

        header->thrash = file->buffer[0] >> 5;

        tmp = file->buffer[0] << 3;
        tmp = tmp >> 3;
        tmp = tmp << 8;
        tmp = tmp | file->buffer[1];

        header->stringfied_tree_size = tmp;

        header->stringfied_tree =
            malloc(sizeof(char) * header->stringfied_tree_size);

        for (int i = 2; i < header->stringfied_tree_size + 2; i++) {
                header->stringfied_tree[i - 2] = file->buffer[i];
        }

        return header;
}

/* Função que descompacta os bits do arquivo compactado e insere em um buffer
 * @param compressed_file: arquivo compactado
 * @param buffer: buffer a ser escrito
 * @param huffman_tree: arvore de huffman
 * @return buffer com os bits do arquivo descompactado
 */
unsigned char *write_decompressed_bits_to_buffer(HFile *compressed_file,
                                                 unsigned char *buffer,
                                                 HTree *huffman_tree,
                                                 int thrash_size) {
        HuffNode *curr = huffman_tree->root;
        int current_index = 0;

        while (current_index < compressed_file->file_size) {
                unsigned char c = compressed_file->buffer[current_index++];

                for (int i = 0; i < 8; i++) {
                        if (is_bit_i_set(c, i)) {
                                curr = curr->right;
                        } else {
                                curr = curr->left;
                        }
                        if (is_leaf(curr)) {
                                buffer =
                                    realloc(buffer, sizeof(buffer) +
                                                        sizeof(curr->data));
                                buffer[sizeof(buffer) - sizeof(curr->data)] =
                                    curr->data;
                                curr = huffman_tree->root;
                                if (current_index ==
                                    compressed_file->file_size - 1) {
                                        return buffer;
                                }
                        }
                }
        }

        return buffer;
}

HuffNode *create_huffman_tree_from_string(unsigned char *buffer, int i) {
        unsigned char currentByte;
        HuffNode *aux;
        currentByte = buffer[i++];
        if (currentByte == '*') {
                aux = create_huffman_node(currentByte, 0);
                aux->left = create_huffman_tree_from_string(buffer, i++);
                aux->right = create_huffman_tree_from_string(buffer, i);
        } else if (currentByte == (char)SLASH) {
                currentByte = buffer[i++];
                aux = create_huffman_node(currentByte, 0);
        } else {
                aux = create_huffman_node(currentByte, 0);
        }
        return aux;
}

/* Função que descompacta um arquivo
 * @param file_name: nome do arquivo a ser descompactado
 */
void decompress(char *file_name) {
        HTree *htree = malloc(sizeof *htree);
        HFile *compressed_file = create_huffman_file(file_name);

        if (compressed_file == NULL) {
                printf("Erro ao abrir o arquivo\n");
                return;
        }

        printf("Removendo .huff ...\n");
        file_name = remove_extension(file_name);

        printf("Recuperando dados do header...\n");
        Header *header = get_header_from_compressed_file(compressed_file);

        printf("Criando a arvore de huffman pela string\n");
        htree->root =
            create_huffman_tree_from_string(header->stringfied_tree, 0);

        printf("criando arquivo descomprimido...\n");
        FILE *decompressed_file = fopen("descomprimido.txt", "w");

        unsigned char *buffer =
            malloc(sizeof *buffer * compressed_file->file_size);

        printf("escrevendo bits descomprimidos no buffer...\n");
        write_decompressed_bits_to_buffer(compressed_file, buffer, htree,
                                          header->thrash);

        printf("escrevendo buffer no arquivo...\n");
        for (int i = 0; i < sizeof(buffer) - sizeof(buffer[0]); i++) {
                fwrite(&buffer[i], sizeof(buffer[0]), 1, decompressed_file);
        }

        fclose(decompressed_file);
        free(htree);
        free(compressed_file);
        free(header);
        free(buffer);
}
