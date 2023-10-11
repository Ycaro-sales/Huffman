#include "list.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define HASH_CAPACITY 255

typedef struct hashtable {
        int array[HASH_CAPACITY];
} Hashtable;

Hashtable *create_hash();

void hash_add(Hashtable *hashtable, unsigned char data);
void hash_remove(Hashtable *hashtable, unsigned char data);
bool hash_search(Hashtable *hashtable, unsigned char data);
int hash_get(Hashtable *hashtable, unsigned char key);
int hash_function(unsigned char key);

#endif // !HASHTABLE_H
