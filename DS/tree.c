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

    if ( pTemp = tree_node_create(t, data) )
    {
        if ( pNewNode = tree_insert2(t, pParent, pTemp) )
            return pNewNode;

        tree_free( (void *) pTemp );
    }

    return NULL;
}

TreeNode *tree_insert2(Tree *t, TreeNode *pParent, TreeNode *pNewNode) 
{
    TreeNode *pTemp;

    if ( pParent && t->ulSize == 0 )
        return NULL;

    pNewNode->pParent = pParent;

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
    
    return NULL;
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


MiniMaxResult tree_minimax(Tree *t, TreeNode *pNode, bool bMax, int (* eval)(void *)) 
{
    MiniMaxResult result = { 0 };
    MiniMaxResult child_result;
    TreeNode *pChild;
    int nBest;

    if ( !pNode )
        pNode = t->pRoot;

    if ( treenode_numofchild(pNode) == 0 ) {
        result.nScore = eval( pNode->data );
        return result;
    }

    nBest = ( bMax ) ? INT_MIN : INT_MAX;

    if ( pNode->pChild ) {
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pNode->pChild); nIdx++ ) {
            pChild = (TreeNode *) llist_getitemAt( (List *) pNode->pChild, nIdx );
#else
        for ( pChild = pNode->pChild; pChild; pChild = pChild->pSibling ) {
#endif
            child_result = tree_minimax( t, pChild, !bMax, eval );
            if ( ((bMax) ? (child_result.nScore > nBest) : (child_result.nScore < nBest)) ) {
                nBest = child_result.nScore;
                result.pBest = (TreeNode *) pChild;
            }
        }
    }

    result.nScore = nBest;
    return result;
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

int tree_height(Tree *t, TreeNode *pParent)
{
    TreeNode *pChild;
    int nMaxHeight, nHeight;

    if ( !pParent )
        pParent = t->pRoot;

    nMaxHeight = -1;

    if ( pParent->pChild ) {
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pParent->pChild); nIdx++ ) {
            pChild = (TreeNode *) llist_getitemAt( (List *) pParent->pChild, nIdx );
#else
        for ( pChild = pParent->pChild; pChild; pChild = pChild->pSibling ) {
#endif
            if ( (nHeight = tree_height(t, pChild)) > nMaxHeight )
                nMaxHeight = nHeight;
        }
    }

    return nMaxHeight + 1;
}

bool tree_path(Tree *t, TreeNode *pParent, TreeNode *pTarget, List *pPath)
{
    TreeNode *pChild;

    if ( !pParent )
        pParent = t->pRoot;

    if ( !llist_insert(pPath, pParent, sizeof(TreeNode), malloc, free, NULL, NULL) )
        return false;

    if ( pParent == pTarget )
        return true;

    if ( pParent->pChild )
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pParent->pChild); nIdx++ ) {
            pChild = (TreeNode *) llist_getitemAt( (List *) pParent->pChild, nIdx );
#else
        for ( pChild = pParent->pChild; pChild; pChild = pChild->pSibling ) {
#endif
            if ( tree_path(t, pChild, pTarget, pPath) )
                return true;
        }

    /* We took the wrong path */
    llist_delete( pPath );
    return false;
}

bool tree_path_lazy(Tree *t, TreeNode *pTarget, List *pPath)
{
    do {
        if ( !llist_insertAtFirst(pPath, pTarget, sizeof(TreeNode), malloc, free, NULL, NULL) )
            return false;
    } while ( pTarget = pTarget->pParent );

    return true;
}

TreeIter *tree_iter_init(Tree *t, TreeNode *pParent, Order order)
{
    TreeIter *pIter;

    if ( !pParent )
        pParent = t->pRoot;

    if ( pIter = (TreeIter *) malloc(sizeof(TreeIter)) ) {
        pIter->order = order;

        switch ( pIter->order ) {
        case PRE_ORDER:
            if ( pIter->pIter = (Stack *) lstack_init() )
                lstack_push( (Stack *) pIter->pIter, &pParent, sizeof(TreeNode *), malloc, free, NULL );
            break;

        case POST_ORDER:
            if ( pIter->pIter = (Queue *) lqueue_init() )
                lqueue_en( (Queue *) pIter->pIter, &pParent, sizeof(TreeNode *), malloc, free, NULL );
            break;

        default:
            pIter->pIter = NULL;
            break;
        }

        if ( !pIter->pIter ) {
            free( pIter );
            pIter = NULL;
        } 

    }

    return pIter;
}

TreeNode *tree_iter_next(TreeIter *pIter) 
{
    TreeNode *pChild, *pNextNode = NULL; 

    if ( pIter->order == PRE_ORDER ) {
        if ( pNextNode = (TreeNode *) lstack_getitem((Stack *) pIter->pIter) ) {
            pNextNode = *(TreeNode **) pNextNode;
            lstack_pop( (Stack *) pIter->pIter );
        }
    }

    else if ( pIter->order == POST_ORDER ) {
        if ( pNextNode = (TreeNode *) lqueue_getitem((Queue *) pIter->pIter) ) {
            pNextNode = *(TreeNode **) pNextNode;
            lqueue_de( (Queue *) pIter->pIter );
        }
    }

    if ( pNextNode && pNextNode->pChild ) {
#ifdef USE_DALGO_STRUCTURES
        for ( int nIdx = 0; nIdx < llist_size((List *) pNextNode->pChild); nIdx++ ) {
            pChild = (TreeNode *) llist_getitemAt( (List *) pNextNode->pChild, nIdx );
#else
        for ( pChild = pNextNode->pChild; pChild; pChild = pChild->pSibling ) {
#endif
            if ( pIter->order == PRE_ORDER ) 
                lstack_push( (Stack *) pIter->pIter, &pChild, sizeof(TreeNode *), malloc, free, NULL );

            else if ( pIter->order == POST_ORDER )
                lqueue_en( (Queue *) pIter->pIter, &pChild, sizeof(TreeNode *), malloc, free, NULL );
        }
    }    

    return pNextNode;
}

void tree_iter_done(TreeIter **ppIter)
{
    if ( (*ppIter)->order == PRE_ORDER ) 
        lstack_cleanup( (Stack **) &(*ppIter)->pIter );

    else if ( (*ppIter)->order == POST_ORDER )
        lqueue_cleanup( (Queue **) &(*ppIter)->pIter );

    free( *ppIter );
    ( *ppIter) = NULL;
}

TreeNode *tree_node_create(Tree *t, void *data) {
    TreeNode *pNewNode;

    if ( pNewNode = (TreeNode *) malloc(sizeof(TreeNode)) )
    {
        if ( pNewNode->data = t->allocate(t->nItemSize) )
        {
            memcpy( pNewNode->data, data, t->nItemSize );
            pNewNode->pParent = NULL;
            pNewNode->pChild = NULL;
            pNewNode->deallocate = t->deallocate;
#ifndef USE_DALGO_STRUCTURES
            pNewNode->pSibling = NULL;
            pNewNode->nChild = 0;
#endif
            return pNewNode;
        }

        free( pNewNode );
    }

    return NULL;
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