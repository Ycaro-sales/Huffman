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

        tmp->used_indexes = create_list();

        return tmp;
}

int hash_function(unsigned char data) { return data % HASH_CAPACITY; }

void hash_add(Hashtable *hashtable, unsigned char data) {
        if (hashtable->array[hash_function(data)] == 0) {
                list_push(hashtable->used_indexes, &data);
        }

        hashtable->array[hash_function(data)]++;
}

void hash_remove(Hashtable *hashtable, unsigned char data) {
        int index = hash_function(data);
        int *pIndex = &index;

        hashtable->array[data] = 0;
        list_remove(hashtable->used_indexes, pIndex);
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
