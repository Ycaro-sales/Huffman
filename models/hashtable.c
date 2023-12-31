#include "hashtable.h"
#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_CAPACITY 255

Hashtable *create_hash() {
        Hashtable *tmp = malloc(sizeof *tmp);

        for (int i = 0; i < HASH_CAPACITY; i++)
                tmp->array[i] = 0;

        return tmp;
}

int hash_function(unsigned char data) { return data % HASH_CAPACITY; }

void hash_add(Hashtable *hashtable, unsigned char data) {
        hashtable->array[hash_function(data)]++;
}

void hash_remove(Hashtable *hashtable, unsigned char data) {
        hashtable->array[data] = 0;
}

bool hash_search(Hashtable *hashtable, unsigned char data) {
        if (hashtable->array[hash_function(data)] > 0) {
                return true;
        }
        return false;
}

int hash_get(Hashtable *hashtable, unsigned char key) {
        return hashtable->array[hash_function(key)];
}
