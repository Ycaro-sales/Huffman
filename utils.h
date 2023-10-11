#ifndef UTILS_H
#define SWAP(x, y)                                                             \
        do {                                                                   \
                typeof(x) temp = (x);                                          \
                (x) = (y);                                                     \
                (y) = temp;                                                    \
        } while (0)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif // !UTILS_H
