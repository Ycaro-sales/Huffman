#include "hashtable.h"
#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Hashtable *create_hashtable(int(hash_function)(unsigned char), int capacity) {
    Hashtable *tmp = malloc(sizeof *tmp);

    tmp->capacity = capacity;
    tmp->hash_function = hash_function;
    tmp->used_indexes = create_list();

    for (int i = 0; i < tmp->capacity; i++)
        tmp->items[i] = 0;
    return tmp;
}

// TODO: essa função assume que não vai ocorrer conflitos
void hash_insert(Hashtable *hashtable, char data) {
    hashtable->items[hashtable->hash_function(data)]++;
    list_append(hashtable->used_indexes, &hash_function(data));
}

void hash_remove(Hashtable *hashtable, char data) {
    hashtable->items[hashtable->hash_function(data)] = 0;
    list_remove(hashtable->used_indexes, &hash_function(data));
}

bool hash_search(Hashtable *hashtable, char data) {
    return hashtable->items[hashtable->hash_function(data)] > 0 ? true : false;
}

int default_hash(unsigned char input) { return input % HASHTABLE_SIZE; }
