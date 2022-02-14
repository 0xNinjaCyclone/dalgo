/*
    Linked List Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
*/

#include "llist.h"

List *llist_init()
{
    List *l = (List *) malloc(sizeof(List));
    if (!l)
        llist_oom();

    return l;
}

int llist_size(List *l)
{
    return l->size;
}

int llist_empty(List *l)
{
    return !l || !l->first || llist_size(l) == 0;
}

int llist_insert(List *l, int item)
{
    /* Insert at the last of the list */

    LNode *temp = (LNode *) malloc(sizeof(LNode));

    if (temp) {
        temp->value = item;
        if (llist_empty(l)) {
            l->first = l->last = temp;
        } else {
            l->last->next = temp;
            l->last = temp;
        }

        temp->next = NULL;
        l->size++;

        return 1;
    } else {
        llist_cleanup(&l);
        llist_oom();
    }
}

int llist_insertAtFirst(List *l, int item)
{
    LNode *temp = (LNode *) malloc(sizeof(LNode));

    if (temp) {
        temp->value = item;
        if (llist_empty(l)) {
            l->first = l->last = temp;
            temp->next = NULL;
        } else {
            temp->next = l->first;
            l->first = temp;
        }

        l->size++;

        return 1;
    } else {
        llist_cleanup(&l);
        llist_oom();
    }
}

int llist_insertAt(List *l, int idx, int item)
{
    LNode *curr, *temp;

    if (idx < 0 || idx > llist_size(l))
        return 0;

    if (idx == 0)
        return llist_insertAtFirst(l, item);

    else if (idx == llist_size(l))
        return llist_insert(l, item);

    else {
        temp = (LNode *) malloc(sizeof(LNode));

        if (temp) {
            curr = l->first;
            for (size_t i = 1; i < idx; i++)
            {
                curr = curr->next;
            }

            temp->value = item;
            temp->next = curr->next;
            curr->next = temp;
            l->size++;

            return 1;
            
        } else {
            llist_cleanup(&l);
            llist_oom();
        }
    }
}

int llist_updateAt(List *l, int idx, int item)
{
    LNode *targetNode; 

    if (llist_empty(l) || idx < 0 || idx >= llist_size(l))
        return 0;

    if (idx == 0)
        l->first->value = item;

    else if (idx == llist_size(l) - 1)
        l->last->value = item;

    else {
        targetNode = l->first;

        for (size_t i = 0; i < idx; i++)
        {
            targetNode = targetNode->next;
        }

        targetNode->value = item;

    }

    return 1;
}

int llist_getitemAt(List *l, int idx)
{
    LNode *targetNode; 

    if (llist_empty(l) || idx < 0 || idx >= llist_size(l))
    {
        llist_cleanup(&l);
        fprintf(stderr,"Error Can't getitem");
        exit(EXIT_FAILURE);
    }

    if (idx == 0)
        return l->first->value;

    else if (idx == llist_size(l) - 1)
        return l->last->value;

    else {
        targetNode = l->first;

        for (size_t i = 0; i < idx; i++)
        {
            targetNode = targetNode->next;
        }

        return targetNode->value;
    }
}

int llist_delete(List *l)
{
    /* Delete last item, return 1 if succeed else 0 */

    LNode *prevLast, *temp;

    if (llist_empty(l))
        return 0;

    if (llist_size(l) == 1) {
        free(l->first);
        l->first = l->last = NULL;
        l->size--;

        return 1;
    }

    prevLast = l->first;

    for (size_t i = 0; i < llist_size(l) - 2; i++)
    {
        prevLast = prevLast->next;
    }

    temp = l->last;
    l->last = prevLast;
    prevLast->next = NULL;
    free(temp);
    l->size--;

    return 1;
    
}

int llist_deleteAtFirst(List *l)
{
    /* Delete last item, return 1 if succeed else 0 */

    LNode *temp;

    if (llist_empty(l))
        return 0;

    if (llist_size(l) == 1) { /* If the list has only one item */
        free(l->first);
        l->first = l->last = NULL;
        l->size--;

        return 1;
    }

    temp = l->first;
    l->first = l->first->next;
    free(temp);
    l->size--;

    return 1;
    
}

int llist_deleteAt(List *l, int idx)
{
    LNode *prev, *temp;

    if (llist_empty(l) || idx < 0 || idx >= llist_size(l))
        return 0;

    if (idx == 0)
        return llist_deleteAtFirst(l);

    else if (idx == llist_size(l) - 1)
        return llist_delete(l);

    else {
        prev = l->first;

        for (size_t i = 0; i < idx - 1; i++)
        {
            prev = prev->next;
        }
        
        temp = prev->next; /* This is the target item */
        prev->next = temp->next;
        free(temp);
        l->size--;

        return 1;
    }
}

int llist_search(List *l, int item)
{
    /* return -1 if didn't find it or positon of the item */

    LNode *temp = l->first;

    if (llist_empty(l))
        return -1;

    for (size_t pos = 0; temp; temp = temp->next, pos++)
    {
        if (temp->value == item)
            return pos;
    }
    
    return -1;
}

void llist_reverse(List *l)
{
    LNode *prev, *curr, *next;

    if (llist_empty(l) || llist_size(l) == 1)
        return;

    prev = NULL;
    curr = l->first;
    next = curr->next;

    while (next)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    l->first = prev;
    
}

void llist_clear(List *l)
{
    while (!llist_empty(l))
    {
        /* 
            (deleteAtFirst) is the best function to do that 
            because its complexity is (Big O(1)) but (delete || deleteAt) is (Big O(n))
        */
        
        llist_deleteAtFirst(l);
    }
    
}

void llist_cleanup(List **l)
{
    /* Free all nodes */
    llist_clear(*l);

    /* Free list handler */
    free(*l);

    /* Set ptr to null to avoid dangling */
    (*l) = NULL;
}

void llist_print(List *l)
{
    LNode *temp = l->first;

    for (size_t counter = 0; temp; temp = temp->next, counter++)
    {
        printf("Value %d => %d\n", counter, temp->value);
    }
    
}

void llist_oom()
{
    fprintf(stderr,"Out Of Memory");
    exit(EXIT_FAILURE);
}

