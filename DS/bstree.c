

#include "bstree.h"

BinarySearchTree *bst_init(int nItemSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    BinarySearchTree *t;

    if ( t = malloc( sizeof(BinarySearchTree) ) )
    {
        t->root = NULL;
        t->lSize = 0;
        t->nItemSize = nItemSize;
        t->allocate = allocate;
        t->deallocate = deallocate;
        t->print = print;
        t->compare = compare;
        return t;
    }

    return NULL;
}

size_t bst_size(BinarySearchTree *t)
{
    return t->lSize;
}

int bst_empty(BinarySearchTree *t)
{
    return bst_size(t) == 0;
}

int bst_insert(BinarySearchTree *t, void *item)
{
    TNode *node;

    if ( node = build_node(t, item) )
        return bst_insert2(t, &t->root, node);

    return 0;
}

int bst_insert2(BinarySearchTree *t, TNode **root, TNode *node)
{
    if ( !(*root) ) 
    {
        ( *root ) = node;
        t->lSize++;
        
        return 1;
    } 
    
    else if ( t->compare((*root)->data, node->data) > 0 )
        // insert at the left, if the new node less than the root
        return bst_insert2(t, &( *root )->left, node);  

    // insert at the right, if the new node larger than the root
    return bst_insert2(t, &( *root )->right, node);
}

int bst_delete(BinarySearchTree *t, OrderType order_type, void *item)
{
    if ( bst_empty(t) )
        return 0;

    int nRet = 0;
    bst_delete2(t, &t->root, order_type, item, &nRet);
    return nRet;
}

void bst_delete2(BinarySearchTree *t, TNode **root, OrderType order_type, void *item, int *nRet)
{
    if ( !(*root) || *nRet ) return;

    switch ( order_type )
    {
    case PRE_ORDER:
        if ( t->compare((*root)->data, item) == 0 )
        {
            ( *nRet )++;
            break;
        }

        bst_delete2(t, &(*root)->left, order_type, item, nRet);
        bst_delete2(t, &(*root)->right, order_type, item, nRet);
        return;

    case IN_ORDER:
        bst_delete2(t, &(*root)->left, order_type, item, nRet);

        if ( t->compare((*root)->data, item) == 0 )
        {
            ( *nRet )++;
            break;
        }

        bst_delete2(t, &(*root)->right, order_type, item, nRet);
        return;

    case POST_ORDER:
        bst_delete2(t, &(*root)->left, order_type, item, nRet);
        bst_delete2(t, &(*root)->right, order_type, item, nRet);

        if ( t->compare((*root)->data, item) == 0 )
        {
            ( *nRet )++;
            break;
        }
    
    default:
        return;
    }

    TNode *minimum_node, *temp;

    if ( (*root)->left && (*root)->right )
    {
        // find the minimum node in the right subtree
        minimum_node = bst_findmin(t, (*root)->right);        

        // move the minimum node to the target
        memmove( (*root)->data, minimum_node->data, t->nItemSize );

        ( *root )->right = bst_deletemin(t, &(*root)->right);

    }

    else if ( (*root)->left )
    {
        temp = (*root);
        (*root) = (*root)->left;
        destroy_node(t, temp); 
    }

    else if ( (*root)->right )
    {
        temp = (*root);
        (*root) = (*root)->right;
        destroy_node(t, temp); 
    }

    else {
        destroy_node(t, *root);
        (*root) = NULL;
    }

    t->lSize--;
}

TNode *bst_deletemin(BinarySearchTree *t, TNode **node)
{
    if ( !(*node) ) return NULL;

    if ( !(*node)->left )
    {
        TNode *temp = (*node)->right;
        destroy_node(t, *node);
        ( *node ) = NULL;
        return temp;
    }

    ( *node )->left = bst_deletemin(t, &(*node)->left);
    return *node;
}

TNode *bst_find(BinarySearchTree *t, OrderType order_type, void *item)
{
    TNode *target = NULL;

    bst_find2(t, t->root, order_type, item, &target);
    return target;
}

void bst_find2(BinarySearchTree *t, TNode *node, OrderType order_type, void *item, TNode **target_node)
{
    if ( !node || *target_node ) return;

    switch ( order_type )
    {
    case PRE_ORDER:
        if ( t->compare(node->data, item) == 0 )
        {
            *target_node = node;
            return;
        }

        bst_find2(t, node->left, order_type, item, target_node);
        bst_find2(t, node->right, order_type, item, target_node);
        break;

    case IN_ORDER:
        bst_find2(t, node->left, order_type, item, target_node);

        if ( t->compare(node->data, item) == 0 )
        {
            *target_node = node;
            return;
        }

        bst_find2(t, node->right, order_type, item, target_node);
        break;

    case POST_ORDER:
        bst_find2(t, node->left, order_type, item, target_node);
        bst_find2(t, node->right, order_type, item, target_node);

        if ( t->compare(node->data, item) == 0 )
            *target_node = node;
    
    default:
        break;
    }

}

TNode *bst_findmax(BinarySearchTree *t, TNode *node)
{
    while ( node->right )
        node = node->right;

    return node;
}

TNode *bst_findmin(BinarySearchTree *t, TNode *node)
{
    while ( node->left )
        node = node->left;

    return node;
}

void bst_print(BinarySearchTree *t, OrderType order_type)
{
    printf("|");
    print_nodes(t, t->root, order_type);
    puts(" |");
}

void bst_cleanup(BinarySearchTree **t)
{
    destroy_nodes( *t, &(*t)->root );
    free( *t );
    ( *t ) = NULL;
}

TNode *build_node(BinarySearchTree *t, void *item)
{
    TNode *node;

    if ( node = malloc( sizeof(TNode) ) )
    {

        node->left = NULL;
        node->right = NULL;
        node->data = t->allocate( t->nItemSize );

        if ( !node->data )
        {
            free( node );
            return NULL;
        }

        memcpy( node->data, item, t->nItemSize );

        return node;
    }

    return NULL;
}

void destroy_nodes(BinarySearchTree *t, TNode **root)
{
    if ( *root )
    {
        // free nodes using post order
        destroy_nodes( t, &(*root)->left );
        destroy_nodes( t, &(*root)->right );
        destroy_node( t, *root );
        ( *root ) = NULL;
    }
}

void destroy_node(BinarySearchTree *t, TNode *node)
{
    t->deallocate( node->data );
    free( node );
}

void print_nodes(BinarySearchTree *t, TNode *node, OrderType order_type)
{
    if ( !node ) return;
    printf(" ");

    switch ( order_type )
    {
    case PRE_ORDER:
        t->print( node->data );
        print_nodes(t, node->left, order_type);
        print_nodes(t, node->right, order_type);
        break;

    case IN_ORDER:
        print_nodes(t, node->left, order_type);
        t->print( node->data );
        print_nodes(t, node->right, order_type);
        break;

    case POST_ORDER:
        print_nodes(t, node->left, order_type);
        print_nodes(t, node->right, order_type);
        t->print( node->data );
        break;
    
    default:
        break;
    }
}

