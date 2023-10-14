#include "compress.h"
#include "../models/hashtable.h"
#include "../utils.h"
#include "huffman_file.h"
#include "huffman_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função que cria os caminhos de cada caracter
 * @param root: raiz da arvore de huffman
 * @return arquivo a ser compactado
 */
void fill_compressed_hash(HuffNode *root, CompressedHash *compressed_hash,
                          char *path) {
        if (is_leaf(root)) {
                compressed_hash->paths[root->data] = path;
        } else {
                char *tmpRight = malloc(sizeof(path) + sizeof(char));
                char *tmpLeft = malloc(sizeof(path) + sizeof(char));

                strncpy(tmpRight, path, sizeof(path) + sizeof(char));
                strncpy(tmpLeft, path, sizeof(path) + sizeof(char));

                fill_compressed_hash(root->left, compressed_hash,
                                     strcat(tmpLeft, "0"));
                fill_compressed_hash(root->right, compressed_hash,
                                     strcat(tmpRight, "1"));
        }
}
/* Função que cria o Hash com os caminhos de cada caracter
 * @param htree: arvore de huffman
 * @return Hash com os caminhos de cada caracter
 */
CompressedHash *create_compressed_hash(HTree *htree) {
        CompressedHash *tmp = malloc(sizeof *tmp);

        char *path = "";

        fill_compressed_hash(htree->root, tmp, path);
        // tmp->thrash;

        return tmp;
}

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
        for (int i = 0; i < 256; i++) {
                if (compressed_hash->paths[file->buffer[i]] > 0) {
                        thrash_size += strlen(compressed_hash->paths[i]) *
                                       file->char_frequency->array[i];
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
        int thrash_size = calculate_thrash_size(compressed_hash, file);
        unsigned char thrash = thrash_size << 5;

        compressed_file = write_thrash_and_tree_size_to_header(
            compressed_file, thrash, huffman_tree->stringfied_tree_size);

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
                    fopen(strcat(compressed_file_name, ".huff"), "wb+");
        } else {
                compressed_file = fopen("file.huff", "wb+");
        }

        printf("Criando arvore de huffman...\n");
        HTree *huffman_tree = create_huffman_tree(file);
        printf("Criando Hashtable de compressão...\n");
        CompressedHash *compressed_hash = create_compressed_hash(huffman_tree);

        printf("abrindo arquivo...\n");
        compressed_file = fopen(compressed_file_name, "wb");

        printf("Criando cabeçalho...\n");
        compressed_file = write_header_to_file(file, compressed_file,
                                               huffman_tree, compressed_hash);
        printf("Escrevendo Bits...\n");
        compressed_file =
            write_bits_to_file(file, compressed_file, compressed_hash);

        fclose(compressed_file);

        printf("%s Compactado com Successo!!\nArquivo compactado: %s\n\n",
               file_name, compressed_file_name);
}
