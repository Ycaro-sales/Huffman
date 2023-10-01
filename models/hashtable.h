#include <stdbool.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define HASHTABLE_SIZE 255

typedef struct Hashtable {
    int capacity;
    int *items[HASHTABLE_SIZE];
    int (*hash_function)(unsigned char);
} Hashtable;

Hashtable *create_hashtable(int(hash_function)(unsigned char), int capacity);

int default_hash(unsigned char);
int hash_function(char data);

bool hash_search(Hashtable *hashtable, char data);
void hash_insert(Hashtable *hashtable, char data);
void hash_remove(Hashtable *hashtable, char data);
#endif // !HASHTABLE_H
