#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

List *create_list() {
        List *tmp = malloc(sizeof *tmp);
        tmp->head = NULL;
        return tmp;
}

void list_append(List *list, void *data) {
        ListNode *tmp = malloc(sizeof *tmp);
        tmp->next = NULL;
        tmp->data = data;

        if (!list->head) {
                list->head = data;
                return;
        }

        ListNode *curr = list->head;
        while (curr->next != NULL) {
                curr = curr->next;
        }

        curr->next = tmp;
}
void list_push(List *list, void *data) {
        ListNode *tmp = malloc(sizeof *tmp);

        tmp->data = data;
        tmp->next = list->head;

        list->head = tmp;
}

void list_print(List *list) {
        ListNode *curr = list->head;

        while (curr->next != NULL) {
                printf("%d", *(int *)curr->data);
                curr = curr->next;
        }
}

bool list_search(List *list, void *data) {
        ListNode *curr = list->head;

        do {
                if (*((int *)curr->data) == *((int *)data)) {
                        return true;
                }
                curr = curr->next;
        } while (curr->next != NULL);

        return false;
}

bool list_remove(List *list, void *data) {
        ListNode *curr = list->head;
        ListNode *tmp = NULL;

        do {
                if (curr->next->data == data) {
                        tmp = curr->next;
                        curr->next = curr->next->next;
                        free(tmp);
                        return true;
                }
                curr = curr->next;
        } while (curr->next != NULL);

        return false;
}
