#ifndef _dalgo_llist
#define _dalgo_llist

#include <stdlib.h>
#include <stdio.h>

typedef struct Node LNode;

struct Node
{
    LNode *next;
    int value;
};

typedef struct 
{
    LNode *first;
    LNode *last;
    int size;
} List;

List *llist_init();
void llist_cleanup(List **l);
int llist_size(List *l);
int llist_empty(List *l);
int llist_insert(List *l, int item);
int llist_insertAt(List *l, int idx, int item);
int llist_insertAtFirst(List *l, int item);
int llist_updateAt(List *l, int idx, int item);
int llist_delete(List *l);
int llist_deleteAtFirst(List *l);
int llist_deleteAt(List *l, int idx);
int llist_getitemAt(List *l, int idx);
int llist_search(List *l, int item);
void llist_reverse(List *l);
void llist_clear(List *l);
void llist_print(List *l);
void llist_oom();

#endif