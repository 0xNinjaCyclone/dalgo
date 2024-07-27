#ifndef _dalgo_tree
#define _dalgo_tree

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "llist.h"

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

Tree *tree_init(int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *));
TreeNode *tree_insert(Tree *t, TreeNode *pParent, void *data);
TreeNode *tree_find(Tree *t, TreeNode *pParent, void *data);
List *tree_findall(Tree *t, TreeNode *pParent, void *data);
void tree_print(Tree *t);
void tree_print2(Tree *t, TreeNode *node);
void tree_free(void *ptr);
void tree_cleanup(Tree **t);

int treenode_numofchild(TreeNode *pParent);

#endif