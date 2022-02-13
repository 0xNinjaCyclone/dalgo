/*
    List Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 12-2-2022
*/

#include "list.h"

List *list_init(int maxsize)
{
    List *l = (List *) malloc(sizeof(List));

    if (l) {
        l->maxsize = maxsize;
        l->size = 0;
        l->values = (int *) malloc(sizeof(int) * l->maxsize);

        if (l->values)
            return l;

        /* Free handler */
        free(l);
        
        goto OOM;
    } else {
        goto OOM;
    }

    OOM :
        fprintf(stderr,"Out Of Memory");
        exit(EXIT_FAILURE);
}

void list_cleanup(List **l)
{
    /* Free values first */
    free((*l)->values);

    /* Then free handler */
    free(*l);

    /* Set ptr to null to avoid dangling */
    *l = NULL;
}

int list_size(List *l)
{
    return l->size;
}

int list_empty(List *l)
{
    return list_size(l) == 0;
}

int list_full(List *l)
{
    return list_size(l) == l->maxsize;
}

int list_insert(List *l, int item)
{
    if (list_full(l))
        return 0;

    l->values[l->size++] = item;

    return 1;
}

int list_insertAt(List *l, int idx, int item)
{
    if (list_full(l) || idx < 0 || idx > l->maxsize)
        return 0;

    /* Shift elements */
    for (size_t i = list_size(l); i > idx; i--)
    {
        l->values[i] = l->values[i - 1];
    }
    
    l->values[idx] = item;
    l->size++;

    return 1;
}

int list_updateAt(List *l, int idx, int item)
{
    if (list_full(l) || idx < 0 || idx > l->maxsize)
        return 0;

    l->values[idx] = item;

    return 1;
}

int list_delete(List *l)
{
    if (list_empty(l))
        return 0;

    l->size--;

    return 1;
}

int list_deleteAt(List *l, int idx)
{
    if (list_empty(l) || idx < 0 || idx > list_size(l))
        return 0;

    /* Shift elements */
    for (size_t i = idx; i < list_size(l); i++)
    {
        l->values[i] = l->values[i + 1];
    }
    
    l->size--;

    return 1;
}

int list_getitem(List *l)
{
    if (!list_empty(l))
        return l->values[l->size - 1];

    else {
        /* Error case */

        if (l) {
            /* handler is initiated, we must cleanup */
            list_cleanup(&l);
        }

        fprintf(stderr,"List is empty");
        exit(EXIT_FAILURE);
    }
}

int list_getitemAt(List *l, int idx)
{
    if (!list_empty(l) && idx >= 0 && idx < list_size(l))
        return l->values[idx];

    else {
        /* Error case */

        if (l) {
            /* handler is initiated, we must cleanup */
            list_cleanup(&l);
        }

        fprintf(stderr,"List is empty");
        exit(EXIT_FAILURE);
    }
}

int list_search(List *l, int item)
{
    for (size_t i = 0; i < list_size(l); i++)
        if (l->values[i] == item)
            return i;

    return -1;
    
}

void list_reverse(List *l)
{
    int swapper, nSize = list_size(l) - 1;

    for (size_t i = 0; i <= nSize / 2; i++)
    {
        swapper = l->values[nSize - i];
        l->values[nSize - i] = l->values[i];
        l->values[i] = swapper;
    }
    
}

void list_clear(List *l)
{
    l->size = 0;
}

void list_print(List *l)
{
    for (size_t i = 0; i < list_size(l); i++)
    {
        printf("Value %d => %d\n", i, list_getitemAt(l, i));
    }
    
}

