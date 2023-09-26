#ifndef HASHTABLE_H
#define HASHTABLE_H
#define HASHTABLE_SIZE 255

typedef struct Node {
    char data;
    int amount;
} Node;
typedef struct Hashtable {
    Node *items[HASHTABLE_SIZE];
} Hashtable;

int hash(char data);

void hash_insert(Hashtable hashtable, char data);
void hash_remove(Hashtable hashtable, char data);
bool hash_search(Hashtable hashtable, char data);

#endif // !HASHTABLE_H
