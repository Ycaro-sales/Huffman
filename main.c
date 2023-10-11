#include "core/compress.h"
#include "core/decompress.h"

#include "models/max_heap.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum options { Compress = 0, Decompress = 1 };

int main(int argc, char *argv[]) {

        if (argc > 1) {
                for (int i = 0; i < argc; ++i) {
                        if (regex_match("^.*\\.(huff)$", argv[i])) {
                                decompress(argv[i]);
                        } else {
                                compress(argv[i]);
                        }
                }
        } else {
                enum options option;
                while (true) {
                        char input[10000];

                        printf("Selecione o arquivo:");
                        scanf("%s\n\n", input);

                        printf("Selecione o que você quer "
                               "fazer:\n--Compactar(0)\n--Descompactar(1)\n\n "
                               "Opção:");
                        scanf("%u\n", &option);

                        switch (option) {
                        case Compress:
                                compress(input);
                        case Decompress:
                                decompress(input);
                        default:
                                printf("Opção invalida. Tente novamente\n");
                        }
                }
        }

        return EXIT_SUCCESS;
}
