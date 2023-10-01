#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

List *create_list(List *list) { List *tmp = malloc(sizeof *tmp); }
void list_append(List *list, void *data);
void list_push(List *list, void *data);
void list_print(List *list);
bool list_free(List *list);
