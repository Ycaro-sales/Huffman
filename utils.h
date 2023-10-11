#include <regex.h>
#include <stdbool.h>
#ifndef UTILS_H
#define SWAP(x, y)                                                             \
        do {                                                                   \
                typeof(x) temp = (x);                                          \
                (x) = (y);                                                     \
                (y) = temp;                                                    \
        } while (0)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

bool regex_match(char *pattern, char *expression);
bool is_bit_set(unsigned char c, int i);
unsigned char set_bit(unsigned char c, int i);
#endif // !UTILS_H
