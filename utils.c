#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *a, void *b, size_t size) {
    void *aux = malloc(size);

    memcpy(aux, a, size);

    memcpy(a, b, size);

    memcpy(b, aux, size);

    free(aux);
}
