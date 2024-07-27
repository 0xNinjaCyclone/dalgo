#ifndef _dalgo_dllist
#define _dalgo_dllist

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node DLNode;

struct Node
{
    DLNode *next;
    DLNode *prev;
    void *data;
    int nSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
    int (* compare)(void *, void *);
};

typedef struct 
{
    DLNode *first;
    DLNode *last;
    size_t lSize;
    DLNode *pLastAccessed;
    size_t ulLastAccessedIdx;
} DoublyLinkedList;


DoublyLinkedList *dllist_init();
size_t dllist_size(DoublyLinkedList *l);
int dllist_empty(DoublyLinkedList *l);
int dllist_insert(DoublyLinkedList *l, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
int dllist_insertAtFirst(DoublyLinkedList *l, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
int dllist_insertAt(DoublyLinkedList *l, size_t lIdx, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
int dllist_updateAt(DoublyLinkedList *l, size_t lIdx, void *item);
void *dllist_getitemAt(DoublyLinkedList *l, size_t lIdx);
int dllist_delete(DoublyLinkedList *l);
int dllist_deleteAtFirst(DoublyLinkedList *l);
int dllist_deleteAt(DoublyLinkedList *l, size_t lIdx);
void dllist_clear(DoublyLinkedList *l);
void dllist_cleanup(DoublyLinkedList **l);
void dllist_print(DoublyLinkedList *l);
DLNode *build_node(void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
void destroy_node(DLNode *node);

#endif