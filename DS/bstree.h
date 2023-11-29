#ifndef _dalgo_bintree
#define _dalgo_bintree

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum { PRE_ORDER, IN_ORDER, POST_ORDER } OrderType;
typedef struct _TNode TNode;

struct _TNode
{
    TNode *left;
    TNode *right;
    void *data;
    
};

typedef struct {
    TNode *root;
    size_t lSize;
    int nItemSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
    int (* compare)(void *, void *);
} BinarySearchTree;


BinarySearchTree *bst_init(int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
size_t bst_size(BinarySearchTree *t);
int bst_empty(BinarySearchTree *t);
int bst_insert(BinarySearchTree *t, void *item);
int bst_insert2(BinarySearchTree *t, TNode **root, TNode *node);
int bst_delete(BinarySearchTree *t, OrderType order_type, void *item);
void bst_delete2(BinarySearchTree *t, TNode **root, OrderType order_type, void *item, int *nRet);
TNode *bst_deletemin(BinarySearchTree *t, TNode **node);
TNode *bst_find(BinarySearchTree *t, OrderType order_type, void *item);
void bst_find2(BinarySearchTree *t, TNode *node, OrderType order_type, void *item, TNode **target_node);
TNode *bst_findmax(BinarySearchTree *t, TNode *node);
TNode *bst_findmin(BinarySearchTree *t, TNode *node);
void bst_print(BinarySearchTree *t, OrderType order_type);
void bst_cleanup(BinarySearchTree **t);

TNode *build_node(BinarySearchTree *t, void *item);
void destroy_nodes(BinarySearchTree *t, TNode **root);
void destroy_node(BinarySearchTree *t, TNode *node);
void print_nodes(BinarySearchTree *t, TNode *node, OrderType order_type);

#endif