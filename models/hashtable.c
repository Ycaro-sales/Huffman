#include "hashtable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 255

Hashtable *create_hashtable(int(hash_function)(unsigned char)) {
    Hashtable *tmp = malloc(sizeof *tmp);

    tmp->hash_function = hash_function;

    for (int i = 0; i < HASHTABLE_SIZE; i++)
        tmp->items[i] = NULL;
    return tmp;
}
Node *create_node(char data) {
    Node *tmp = malloc(sizeof *tmp);

    tmp->amount = 1;
    tmp->data = data;

    return tmp;
}

void hash_insert(Hashtable *hashtable, char data) {
    Node *tmp = create_node(data);

    hashtable->items[hashtable->hash_function(data)] = tmp;
}

void hash_remove(Hashtable *hashtable, char data) {
    Node *tmp = NULL;

    free(hashtable->items[hashtable->hash_function(data)]);

    hashtable->items[hashtable->hash_function(data)] = tmp;
}

bool hash_search(Hashtable *hashtable, char data) {
    if (hashtable->items[hashtable->hash_function(data)])
        return true;
    return false;
}
