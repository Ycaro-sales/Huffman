#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char set_bit(unsigned char c, int i) {
        unsigned char mask = 1 << i;
        return mask | c;
}
