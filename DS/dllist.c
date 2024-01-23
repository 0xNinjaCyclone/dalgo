/*
    Doubly Linked List Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 18-12-2023
*/

#include "dllist.h"

DoublyLinkedList *dllist_init()
{
    DoublyLinkedList *l;

    if ( l = malloc( sizeof(DoublyLinkedList) ) )
    {
        l->first = l->last = NULL;
        l->lSize = 0;
        return l;
    }

    return NULL;
}

size_t dllist_size(DoublyLinkedList *l)
{
    return l->lSize;
}

int dllist_empty(DoublyLinkedList *l)
{
    return !l->first || dllist_size(l) == 0;
}

int dllist_insert(DoublyLinkedList *l, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    DLNode *node;

    if ( node = build_node(item, nItemSize, allocate, deallocate, print, compare) )
    {
        if ( dllist_empty(l) )
            l->first = l->last = node;
        else {
            node->prev = l->last;
            l->last->next = node;
            l->last = node;
        }

        l->lSize++;

        return 1;
    }

    return 0;
}

int dllist_insertAtFirst(DoublyLinkedList *l, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    DLNode *node;

    if ( node = build_node(item, nItemSize, allocate, deallocate, print, compare) )
    {
        if ( dllist_empty(l) )
            l->first = l->last = node;
        else {
            node->next = l->first;
            node->prev = node;
            l->first = node;
        }

        l->lSize++;

        return 1;
    }

    return 0;
}

int dllist_insertAt(DoublyLinkedList *l, size_t lIdx, void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    DLNode *node, *curr;

    if ( lIdx < 0 || lIdx > dllist_size(l) )
        return 0;

    if ( lIdx == 0 )
        return dllist_insertAtFirst(l, item, nItemSize, allocate, deallocate, print, compare);

    else if ( lIdx == dllist_size(l) )
        return dllist_insert(l, item, nItemSize, allocate, deallocate, print, compare);

    else {
        /* Build the node and return if built failed */
        if ( !(node = build_node(item, nItemSize, allocate, deallocate, print, compare)) )
            return 0;

        /* Find the item before the target */
        if ( lIdx <= dllist_size(l) / 2 )
            /* Move from the beginning */
            for (
                curr = l->first; 
                --lIdx; 
                curr = curr->next
            );

        else 
            /* Search backward */
            for (
                lIdx -= dllist_size(l),
                curr = l->last;
                lIdx++;
                curr = curr->prev
            );

        node->next = curr->next;
        node->prev = curr;
        curr->next->prev = node;
        curr->next = node;
        l->lSize++;

        return 1;
    }
}

int dllist_updateAt(DoublyLinkedList *l, size_t lIdx, void *item)
{
    DLNode *node;

    if ( lIdx < 0 || lIdx > dllist_size(l) )
        return 0;

    if ( lIdx == 0 )
        memcpy( l->first->data, item, l->first->nSize );

    else if ( lIdx == dllist_size(l) - 1 )
        memcpy( l->last->data, item, l->last->nSize );

    else {
        /* Find the target node */
        if ( lIdx <= dllist_size(l) / 2 )
            /* Search from the beginning */
            for (
                node = l->first; 
                lIdx--; 
                node = node->next
            );

        else 
            /* Search backward */
            for (
                lIdx -= dllist_size(l),
                node = l->last;
                ++lIdx;
                node = node->prev
            );

        memcpy( node->data, item, node->nSize );
    }   

    return 1;
}

void *dllist_getitemAt(DoublyLinkedList *l, size_t lIdx)
{
    DLNode *node;

    if ( lIdx < 0 || lIdx > dllist_size(l) )
        return NULL;

    if ( lIdx == 0 )
        return l->first->data;

    else if ( lIdx == dllist_size(l) - 1 )
        return l->last->data;

    else {
        /* Find the target node */

        if ( lIdx <= dllist_size(l) / 2 )
            for (
                node = l->first; 
                lIdx--; 
                node = node->next
            );

        else 
            /* Search backward */
            for (
                lIdx -= dllist_size(l),
                node = l->last;
                ++lIdx;
                node = node->prev
            );

        return node->data;
    }   

}

int dllist_delete(DoublyLinkedList *l)
{
    /* Delete the last item, return 1 if succeed else 0 */

    DLNode *temp;

    if ( dllist_empty(l) )
        return 0;

    if ( dllist_size(l) == 1 ) {
        destroy_node( l->first );
        l->first = l->last = NULL;
        l->lSize--;

        return 1;
    }

    temp = l->last;
    l->last = l->last->prev;
    l->last->next = NULL;
    destroy_node( temp );
    l->lSize--;

    return 1;
}

int dllist_deleteAtFirst(DoublyLinkedList *l)
{
    /* Delete the first item, return 1 if succeed else 0 */

    DLNode *temp;

    if ( dllist_empty(l) )
        return 0;

    /* if there is only one item */
    if ( dllist_size(l) == 1 ) {
        destroy_node( l->first );
        l->first = l->last = NULL;
        l->lSize--;

        return 1;
    }

    temp = l->first;
    l->first = l->first->next;
    l->first->prev = NULL;
    destroy_node( temp );
    l->lSize--;

    return 1;
}

int dllist_deleteAt(DoublyLinkedList *l, size_t lIdx)
{
    DLNode *prev, *temp;

    if ( dllist_empty(l) || lIdx >= dllist_size(l) )
        return 0;

    if ( lIdx == 0 )
        return dllist_deleteAtFirst(l);

    else if ( lIdx == dllist_size(l) - 1 )
        return dllist_delete(l);

    else {
        /* Find the node before target */
        if ( lIdx <= dllist_size(l) / 2 )
            for (
                prev = l->first; 
                --lIdx; 
                prev = prev->next
            );

        else 
            /* Search backward */
            for (
                lIdx -= dllist_size(l),
                prev = l->last;
                lIdx++;
                prev = prev->prev
            );

        temp = prev->next; /* This is the target item */
        prev->next = temp->next;
        temp->next->prev = prev;
        destroy_node( temp );
        l->lSize--;

        return 1;
    }
}

void dllist_clear(DoublyLinkedList *l)
{
    while ( !dllist_empty(l) )
    {
        /* 
            (deleteAtFirst) is the best function to do that 
            because its complexity is (Big O(1)) but (delete || deleteAt) is (Big O(n))
        */
        
        dllist_deleteAtFirst( l );
    }
}

void dllist_cleanup(DoublyLinkedList **l)
{
    /* Free all nodes */
    dllist_clear( *l );

    /* Free list handler */
    free( *l );

    /* Set ptr to null to avoid dangling */
    ( *l ) = NULL;
}

void dllist_print(DoublyLinkedList *l)
{
    DLNode *node;

    printf("[ ");

    if ( node = l->first )
    {
        do {
            node->print( node->data );
            if ( node->next ) printf(", ");
        } while ( node = node->next );
    }

    printf(" ]");
}

DLNode *build_node(void *item, int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    DLNode *node;

    if ( node = malloc( sizeof(DLNode) ) )
    {
        node->allocate = allocate;
        node->deallocate = deallocate;
        node->print = print;
        node->compare = compare;
        node->nSize = nItemSize;
        node->next = NULL;
        node->prev = NULL;
        node->data = node->allocate( node->nSize );

        if ( !node->data )
        {
            free( node );
            return NULL;
        }

        memcpy( node->data, item, node->nSize );

        return node;
    }

    return NULL;
}

void destroy_node(DLNode *node)
{
    node->deallocate( node->data );
    free( node );
}