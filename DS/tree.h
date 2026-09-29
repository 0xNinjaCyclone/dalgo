#ifndef _dalgo_tree
#define _dalgo_tree

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "llist.h"
#include "lstack.h"
#include "lqueue.h"

typedef struct _TreeNode TreeNode;

struct _TreeNode {
    TreeNode *pParent;
    void *pChild;
#if !defined(USE_DALGO_STRUCTURES)
    TreeNode *pSibling;
    int nChild;
#endif
    void *data;
    void (* deallocate)(void *);
};

typedef struct {
    TreeNode *pRoot;
    size_t ulSize;
    int nItemSize;
    void *(* allocate)(size_t);
    void (* deallocate)(void *);
    void (* print)(void *);
    int (* compare)(void *, void *);
} Tree;

typedef struct {
    TreeNode *pBest;
    int nScore;
} MiniMaxResult;

typedef enum { 
    PRE_ORDER,
    POST_ORDER
} Order;

typedef struct {
    Order order;
    void *pIter;
} TreeIter;

Tree *tree_init(int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
TreeNode *tree_insert(Tree *t, TreeNode *pParent, void *data);
TreeNode *tree_insert2(Tree *t, TreeNode *pParent, TreeNode *pNewNode);
MiniMaxResult tree_minimax(Tree *t, TreeNode *pNode, bool bMax, int (* eval)(void *));
TreeNode *tree_find(Tree *t, TreeNode *pParent, void *data);
List *tree_findall(Tree *t, TreeNode *pParent, void *data);
int tree_height(Tree *t, TreeNode *pParent);
bool tree_path(Tree *t, TreeNode *pParent, TreeNode *pTarget, List *pPath);
bool tree_path_lazy(Tree *t, TreeNode *pTarget, List *pPath);
TreeIter *tree_iter_init(Tree *t, TreeNode *pParent, Order order);
TreeNode *tree_iter_next(TreeIter *pIter);
void tree_iter_done(TreeIter **ppIter);
TreeNode *tree_node_create(Tree *t, void *data);
void tree_print(Tree *t);
void tree_print2(Tree *t, TreeNode *node);
void tree_free(void *ptr);
void tree_cleanup(Tree **t);

int treenode_numofchild(TreeNode *pParent);


#endif
