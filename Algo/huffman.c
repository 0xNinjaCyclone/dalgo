
#include "huffman.h"

HuffmanTreeNode *huffman_calcfreq(unsigned char *data, size_t ulSize, size_t *ulpNumberOfNodes)
{
    HuffmanTreeNode *pNodes;
    Hash *htable;
    Key *pKey;
    Item *pItem;
    size_t ulCtr, ulIdx;

    if ( !(htable = hash_new(256, REPLACEMENT)) )
        return NULL;

    // Iterate over all bytes to be inserted into a hash table with their frequency
    while ( ulSize-- )
    {
        if ( pKey = hash_getkey(htable, data, sizeof(unsigned char)) )
        {
            ulCtr = *(size_t *) hash_get(htable, pKey) + 1;
            pItem = item_new(&ulCtr, sizeof(size_t), malloc, free, NULL, ULongCmp);
            hash_update(htable, pKey, pItem);
        } 
        
        else {
            ulCtr = 1;
            pKey = key_new(data, sizeof(unsigned char), NULL, ByteCmp);
            pItem = item_new(&ulCtr, sizeof(size_t), malloc, free, NULL, ULongCmp);
            hash_insert(htable, pKey, pItem);
        }
        
        data++;
    }

    // Set the number of nodes
    ( *ulpNumberOfNodes ) = hash_size(htable);

    // Allocate memory for the nodes
    if ( !(pNodes = (HuffmanTreeNode *) malloc(*ulpNumberOfNodes * sizeof(HuffmanTreeNode))) )
    {
        hash_destroy( &htable );
        return NULL;
    }

    ulIdx = ulCtr = 0;

    while ( hash_next(htable, &ulCtr, &pKey, &pItem) )
    {
        ( pNodes + ulIdx )->data = *(unsigned char *) pKey->data;
        ( pNodes + ulIdx )->ulFrequency = *(unsigned long *) hash_get( htable, pKey );
        ( pNodes + ulIdx )->left = NULL;
        ( pNodes + ulIdx )->right = NULL;
        ulIdx++;
    }
    
    hash_destroy( &htable );

    return pNodes;
}

int huffman_cmpnode(void *x, void *y)
{
    return ULongCmp(
        &( (HuffmanTreeNode *) x )->ulFrequency,
        &( (HuffmanTreeNode *) y )->ulFrequency
    );
}

HuffmanTreeNode *huffman_newnode(HuffmanTreeNode *node)
{
    HuffmanTreeNode *hpNode;

    if ( hpNode = malloc(sizeof(HuffmanTreeNode)) )
    {
        hpNode->data = node->data;
        hpNode->ulFrequency = node->ulFrequency;
        hpNode->left = node->left;
        hpNode->right = node->right;
        return hpNode;    
    }

    return NULL;
}

HuffmanTreeNode *huffman_build(HuffmanTreeNode *hNodes, size_t ulSize)
{
    Heap *htree;
    HuffmanTreeNode *hpLeftTreeNode, *hpRightTreeNode, *hpTreeNode;
    HuffmanTreeNode hLeftNode, hRightNode, hNode;

    if ( !(htree = heap_init(ulSize, sizeof(HuffmanTreeNode), MINHEAP, malloc, free, NULL, huffman_cmpnode)) )
        return NULL;
    
    if ( ! heap_build(htree, hNodes, ulSize) )
    {
        heap_cleanup( &htree );
        return NULL;
    }
    
    while ( heap_size(htree) > 1 )
    {
        hLeftNode = *(HuffmanTreeNode *) heap_root(htree)->data;
        hpLeftTreeNode = huffman_newnode( &hLeftNode );
        heap_delete(htree, &hLeftNode);
        hRightNode = *(HuffmanTreeNode *) heap_root(htree)->data;
        hpRightTreeNode = huffman_newnode( &hRightNode );
        heap_delete(htree, &hRightNode);
        hNode.ulFrequency = hLeftNode.ulFrequency + hRightNode.ulFrequency;
        hNode.left = hpLeftTreeNode;
        hNode.right = hpRightTreeNode;
        hNode.data = 0x00;
        hpTreeNode = huffman_newnode( &hNode );
        heap_insert(htree, &hNode);
    }

    hNode = *(HuffmanTreeNode *) heap_root( htree )->data;
    hpTreeNode = huffman_newnode( &hNode );
    heap_delete(htree, &hNode);
    heap_cleanup( &htree );

    return hpTreeNode;
}

void huffman_cleanup(HuffmanTreeNode **root)
{
    if ( (*root)->left )
        huffman_cleanup( &(*root)->left );

    if ( (*root)->right )
        huffman_cleanup( &(*root)->right );

    if ( !(*root)->left && !(*root)->right )
    {
        free( *root );
        ( *root ) = NULL;
    }
}
