#include <stdbool.h>

#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
} List;

List *create_list();
void list_append(List *list, void *data);
void list_push(List *list, void *data);
void list_print(List *list);
bool list_free(List *list);
bool list_remove(List *remove, void *data);

#endif // !LIST_H
