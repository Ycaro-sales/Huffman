#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char set_bit(unsigned char c, int i) {
        unsigned char mask = 1 << i;
        return mask | c;
}

bool is_bit_i_set(unsigned char c, int i) {
        unsigned char mask = 1 << i;
        return mask & c;
}

bool regex_match(char *pattern, char *expression) {
        regex_t *regex;
        /* compila a ER passada em argv[1]
         * em caso de erro, a função retorna diferente de zero */
        if (regcomp(regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
                fprintf(stderr, "erro regcomp\n");
                exit(1);
        }

        /* tenta casar a ER compilada (&reg) com a entrada (argv[2])
         * se a função regexec retornar 0 casou, caso contrário não */
        if ((regexec(regex, expression, 0, (regmatch_t *)NULL, 0)) == 0)
                return true;
        else
                return false;
}
