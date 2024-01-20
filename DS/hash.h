#ifndef _dalgo_hash
#define _dalgo_hash

#include <stdlib.h>
#include <string.h>
#include "llist.h"

typedef struct
{
    void *data;
    int nSize;
    void (* print)(void *);
    int (* compare)(void *, void *);
} Key;

typedef struct
{
    void *data;
    int nSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
    int (* compare)(void *, void *);
} Item;

typedef struct
{
    Key *key;
    Item *item;
} Node;

typedef enum
{
    REPLACEMENT,
    OPEN_ADDRESSING,
    CHAINING
} HType;

typedef struct 
{
    void **data;
    size_t lSize;
    size_t lMaxSize;
    size_t lCollisions;
    size_t lNextItemIdx; // last accessed item by hash_next function
    HType type;
} Hash;


Key *key_new(void *data, int nSize, void (* print)(void *), int (* compare)(void *, void *));
size_t key_hash(Key *k, size_t lMaxSize);
void key_destroy(Key **k);

Item *item_new(void *data, int nSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
void item_destroy(Item **i);

Node *node_new(Key *k, Item *i);
int node_compare(void *node, void *key); // Callback for the list
void node_destroy(Node **node);

Hash *hash_new(size_t lMaxSize, HType type);
int hash_insert(Hash *h, Key *k, Item *i);
void *hash_get(Hash *h, Key *k);
Item *hash_get2(Hash *h, Key *k);
int hash_delete(Hash *h, Key *k);
int hash_next(Hash *h, size_t *lPos, Key **k, Item **i); // lIdx needed in CHAINING type, can be set NULL for othrt types
void hash_print(Hash *h);
void hash_destroy(Hash **h);

#endif