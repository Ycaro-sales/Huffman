#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_CAPACITY 255

typedef struct hashtable {
    int array[HASH_CAPACITY];
    List *used_indexes;
} Hashtable;

Hashtable *create_hash() {
    Hashtable *tmp = malloc(sizeof *tmp);
    tmp->used_indexes = create_list();

    return tmp;
}

int hash_function(unsigned char *data) { return (int)data[0] % HASH_CAPACITY; }

void hash_add(Hashtable *hashtable, unsigned char *data) {
    if (hashtable->array[hash_function(data)] == 0) {
        list_push(hashtable->used_indexes, &data);
    }

    hashtable->array[hash_function(data)]++;
}

bool hash_remove(Hashtable *hashtable, unsigned char *data) {
    if (hashtable->array[hash_function(data)] == 0) {
        return false;
    }

    hashtable->array[hash_function(data)] = 0;
    return true;
}

bool hash_search(Hashtable *hashtable, unsigned char *data) {
    if (hashtable->array[hash_function(data)] > 0) {
        return true;
    }
    return false;
}

int hash_get(Hashtable *hashtable, unsigned char key) {
    return hashtable->array[hash_function(&key)];
}
