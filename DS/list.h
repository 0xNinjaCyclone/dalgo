#ifndef _dalgo_list
#define _dalgo_list

#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    int *values;
    int size;
    int maxsize;
} List;

List *list_init(int maxsize);
void list_cleanup(List **l);
int list_size(List *l);
int list_empty(List *l);
int list_full(List *l);
int list_insert(List *l, int item);
int list_insertAt(List *l, int idx, int item);
int list_updateAt(List *l, int idx, int item);
int list_delete(List *l);
int list_deleteAt(List *l, int idx);
int list_getitem(List *l);
int list_getitemAt(List *l, int idx);
int list_search(List *l, int item);
void list_reverse(List *l);
void list_clear(List *l);
void list_print(List *l);

#endif