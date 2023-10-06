#include "list.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct hashtable {
    int array[sizeof(unsigned char)];
    List *used_indexes;
} Hashtable;

Hashtable *create_hash();

void hash_add(Hashtable *hashtable, unsigned char data);
bool hash_remove(Hashtable *hashtable, unsigned char data);
bool hash_search(Hashtable *hashtable, unsigned char data);
int hash_get(Hashtable *hashtable, unsigned char key);
int hash_function(unsigned char key);

#endif // !HASHTABLE_H
