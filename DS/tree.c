/*
    General Tree Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 23-07-2024
*/

#include "tree.h"

Tree *tree_init(int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    Tree *t;

    if ( t = (Tree *) malloc( sizeof(Tree) ) )
    {
        t->pRoot = NULL;
        t->ulSize = 0;
        t->nItemSize = nItemSize;
        t->allocate = allocate;
        t->deallocate = deallocate;
        t->print = print;
        t->compare = compare;
    }

    return t;
}

TreeNode *tree_insert(Tree *t, TreeNode *pParent, void *data)
{
    TreeNode *pNewNode, *pTemp;

    if ( pParent && t->ulSize == 0 )
        return NULL;

    if ( pNewNode = (TreeNode *) malloc(sizeof(TreeNode)) )
    {
        if ( pNewNode->data = t->allocate(t->nItemSize) )
        {
            memcpy(pNewNode->data, data, t->nItemSize);
            pNewNode->pParent = pParent;
            pNewNode->pChild = NULL;
            pNewNode->deallocate = t->deallocate;
#ifndef USE_DALGO_STRUCTURES
            pNewNode->pSibling = NULL;
            pNewNode->nChild = 0;
#endif

            if ( !t->pRoot ) {
                t->pRoot = pNewNode;
                t->ulSize++;
                return t->pRoot;
            }

            if ( !pParent )
                pParent = t->pRoot;

#ifdef USE_DALGO_STRUCTURES
            if ( !pParent->pChild )
                pParent->pChild = (void *) llist_init();

            if ( pParent->pChild )
                if ( llist_insert((List *)pParent->pChild, pNewNode, sizeof(TreeNode), malloc, tree_free, NULL, NULL) )
                {
                    free( pNewNode );
                    t->ulSize++;
                    return (TreeNode *) llist_getitemAt( (List *)pParent->pChild, llist_size((List *)pParent->pChild)-1 );
                }
            
#else
            if ( pTemp = (TreeNode *) pParent->pChild ) {
                while ( pTemp->pSibling )
                    pTemp = pTemp->pSibling;
            
                pTemp->pSibling = pNewNode;
            }

            else {
                pParent->pChild = (void *) pNewNode;
            }

            t->ulSize++;
            pParent->nChild++;

            return pNewNode;
#endif
        }

        free( pNewNode );
    }

    return NULL;
}

TreeNode *tree_find(Tree *t, TreeNode *pParent, void *data)
{
    TreeNode *pTarget;
    void *pChild;

    if ( t->ulSize == 0 )
        return NULL;

    if ( !pParent )
        pParent = t->pRoot;

    if ( t->compare(pParent->data, data) == 0 )
        return pParent;

    if ( pChild = pParent->pChild ) {
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pChild); nIdx++ )
            if ( pTarget = tree_find(t, (TreeNode *) llist_getitemAt((List *) pChild, nIdx), data) )
                return pTarget;
#else
        do {
            if ( pTarget = tree_find(t, (TreeNode *) pChild, data) )
                return pTarget;
        } while ( pChild = ((TreeNode *) pChild)->pSibling );
#endif
    }

    return NULL;
}

static void tree_findnodes(Tree *t, TreeNode *pParent, void *data, List *pResult)
{
    void *pChild;

    if ( t->compare(pParent->data, data) == 0 )
        llist_insert( pResult, (void *) pParent, sizeof(TreeNode), malloc, free, NULL, NULL );

    if ( pChild = pParent->pChild )
    {
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pChild); nIdx++ )
            tree_findnodes( t, (TreeNode *) llist_getitemAt((List *) pChild, nIdx), data, pResult );
#else
        do {
            tree_findnodes( t, (TreeNode *) pChild, data, pResult );
        } while ( pChild = ((TreeNode *) pChild)->pSibling );
#endif
    }
}

List *tree_findall(Tree *t, TreeNode *pParent, void *data)
{
    List *pTreeNodes = NULL;

    if ( t->ulSize )
        if ( pTreeNodes = llist_init() )
            tree_findnodes( t, (pParent) ? pParent : t->pRoot, data, pTreeNodes );

    return pTreeNodes;
}

void tree_print(Tree *t)
{
    tree_print2(t, t->pRoot);
}

void tree_print2(Tree *t, TreeNode *node)
{
    void *pChild;
    static int nDepth = 0;

    if ( t->ulSize == 0 )
        return;

    for ( int i = 0; i < nDepth*2; i++ ) 
        putchar(' ');

    nDepth++;
    t->print( node->data );
    putchar('\n');

    if ( pChild = node->pChild ) {
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pChild); nIdx++ )
            tree_print2(t, (TreeNode *) llist_getitemAt((List *) pChild, nIdx));

#else
        do {
            tree_print2(t, (TreeNode *) pChild);
        } while ( pChild = ((TreeNode *) pChild)->pSibling );

#endif
        putchar('\n');
    }

    nDepth--;
}


void tree_free(void *ptr)
{
#ifndef USE_DALGO_STRUCTURES
    TreeNode *pNode, *pNext;
#endif

    if ( ((TreeNode *) ptr)->pChild )
    {
#ifdef USE_DALGO_STRUCTURES
        llist_cleanup( (List **)&((TreeNode *) ptr)->pChild );
#else
        pNode = ((TreeNode *) ptr)->pChild;

        while ( pNode )
        {
            pNext = pNode->pSibling;
            tree_free( (void *) pNode );
            pNode = pNext;
        }
#endif
    }

    ((TreeNode *) ptr)->deallocate( ((TreeNode *) ptr)->data );
    free( ptr );
}


void tree_cleanup(Tree **t)
{
    if ( (*t)->pRoot )
        tree_free( (void *)(*t)->pRoot );
    
    free( *t );
    *t = NULL;
}

int treenode_numofchild(TreeNode *pParent)
{
#ifdef USE_DALGO_STRUCTURES
    return ( pParent->pChild ) ? (int) llist_size( (List *) pParent->pChild ) : 0;
#else
    return pParent->nChild;
#endif
}