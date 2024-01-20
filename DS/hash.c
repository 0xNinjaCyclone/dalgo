/*
    Hash Table Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 18-1-2024
*/

#include "hash.h"

Key *key_new(void *data, int nSize, void (* print)(void *), int (* compare)(void *, void *))
{
    Key *k;

    if ( k = malloc(sizeof(Key)) )
    {
        k->print = print;
        k->compare = compare;
        k->nSize = nSize;

        if ( k->data = malloc(k->nSize) )
        {
            memcpy(k->data, data, k->nSize);
            return k;
        }

        free( k );
    }

    return NULL;
}

size_t key_hash(Key *k, size_t lMaxSize)
{
    size_t hash = 0;

    for (size_t ctr = 0; ctr < k->nSize; ctr++)
        hash += *( (unsigned char *) k->data + ctr );

    return hash % lMaxSize;
}

void key_destroy(Key **k)
{
    free( (*k)->data );
    free( *k );
    ( *k ) = NULL;
}

Item *item_new(void *data, int nSize, void *(* allocate)(size_t), void (* deallocate)(void *), void (* print)(void *), int (* compare)(void *, void *))
{
    Item *i;

    if ( i = malloc(sizeof(Item)) )
    {
        i->allocate = allocate;
        i->deallocate = deallocate;
        i->print = print;
        i->compare = compare;
        i->nSize = nSize;

        if ( i->data = i->allocate(i->nSize) )
        {
            memcpy(i->data, data, i->nSize);
            return i;
        }

        free( i );
    }

    return NULL;
}

void item_destroy(Item **i)
{
    ( *i )->deallocate( (*i)->data );
    free( *i );
    ( *i ) = NULL;
}

Node *node_new(Key *k, Item *i)
{
    Node *node;

    if ( node = malloc(sizeof(Node)) )
    {
        node->key = k;
        node->item = i;
        return node;
    }

    return NULL;
}

// Callback for the list
int node_compare(void *node, void *key)
{
    Node *n;
    int r;
    
    // We store the addresses of the nodes, so we dereferencing in this way
    n = *(Node **) node; 

    // Compare the sizes of the keys
    if ( n->key->nSize != ((Key *) key)->nSize ) // if the types are not same
        return n->key->nSize - ((Key *) key)->nSize;

    return n->key->compare( n->key->data, ((Key *) key)->data );
}

void node_destroy(Node **node)
{
    free( *node );
    ( *node ) = NULL;
}

Hash *hash_new(size_t lMaxSize, HType type)
{
    Hash *h;

    if ( h = malloc(sizeof(Hash)) )
    {
        h->lMaxSize = lMaxSize;
        h->lSize = h->lCollisions = h->lNextItemIdx = 0;
        h->type = type;

        if ( h->data = malloc(sizeof(void *) * (h->lMaxSize + 1)) )
        {
            do {
                h->data[ lMaxSize ] = NULL;
            } while( lMaxSize-- );

            return h;
        }

        free( h );
    }

    return NULL;
}

int hash_insert(Hash *h, Key *k, Item *i)
{
    void **temp;
    Node *node;
    size_t hash, lCtr;

    // Generate a hash from the key
    hash = key_hash( k, h->lMaxSize );

    if ( h->type == REPLACEMENT )
    {
        if ( ! h->data[hash] )
        {
            if ( !(node = node_new(k, i)) )
                return 0;

            h->lSize++;
        } else { // Collision case
            node = (Node *) h->data[hash];
            h->lCollisions++;
        }

        node->key = k;
        node->item = i;

        // Insert the node into the table
        h->data[ hash ] = (void *) node;
    }

    else if ( h->type == OPEN_ADDRESSING )
    {
        // Check if there are no available entries
        if ( h->lSize == h->lMaxSize )
            return 0;

        // Pointing now to the suitable entry
        temp = h->data + hash;

        // Check whether this entry is available or not
        if ( *temp )
        {
            // Check if the given key was used before
            if ( node_compare(temp, k) == 0 )
                return 0;

            // This is a f*cking collision case
            h->lCollisions++;

            lCtr = h->lMaxSize - 1 - hash;

            // Find an unused entry next to the entry
            while ( lCtr-- && *(++temp) );
            

            // WHAT THE FUCK IF ALL ENTRIES ON THE RIGHT WERE UNAVAILABLE ???
            if ( lCtr < 0 )
            {
                // Pointing now to the suitable entry
                temp = h->data + hash;

                // The index of the entry
                lCtr = hash;

                // Search backword until find an available entry
                while ( lCtr-- && *(--temp) );
            }
        }

        // Create the node
        if ( !(node = node_new(k, i)) )
            return 0;

        node->key = k;
        node->item = i;

        // insert into the table
        ( *temp ) = (void *) node;
        
        h->lSize++;
    }

    else if ( h->type == CHAINING )
    {
        // Initialize a list for this entry if was not initialized yet
        if ( ! h->data[hash] )
            if ( !(h->data[hash] = (void *) llist_init()) )
                return 0;

        // Create a node
        if ( !(node = node_new(k, i)) )
            return 0;

        // Collision check
        if ( ! llist_empty((List *) h->data[hash]) )
        {
            // Check if the given key was used before
            if ( llist_search((List *) h->data[hash], (void *) k, sizeof(Node *)) != -1 )
                return 0;

            h->lCollisions++;
        }

        if ( ! llist_insert(
            (List *) h->data[hash],
            (void *) &node, // Insert the address of the node, not the node itself
            sizeof(void *),
            malloc, // malloc and free are suitable for dealing with the node address (we don't need to develop custom allocators)
            free,
            NULL,  // We don't need to print the node.
            node_compare
        ) )
            // Something goes wrong
            return 0;

        h->lSize++;
    }

    else // Unsupported type
        return 0;

    return 1;
}

void *hash_get(Hash *h, Key *k)
{
    Item *i;

    // Get the item by the key
    if ( ! (i = hash_get2(h, k)) )
        return NULL;

    return i->data;
}

Item *hash_get2(Hash *h, Key *k)
{
    void *ent;
    size_t hash, lPos;

    // Calculate the hash
    hash = key_hash(k, h->lMaxSize);

    // Find the target entry
    if ( ent = h->data[hash] )
    {
        if ( h->type == REPLACEMENT )
            return ((Node *) ent)->item;

        else if ( h->type == OPEN_ADDRESSING )
        {
            lPos = hash;
            
            // Find the node
            do {
                ent = h->data[ lPos ];
                
                if ( ent && node_compare(&ent, (void *) k) == 0 )
                    break;

            } while ( ++lPos != h->lMaxSize );
            
            // If the node was not on the right
            if ( lPos == h->lMaxSize )
            {
                // If we were searching from the beginning 
                if ( hash == 0 )
                    return 0;

                // Pointing now to the suitable entry
                ent = h->data[hash];

                lPos = hash;

                // Search backword
                do {
                    ent = h->data[ lPos ];
                } while ( node_compare(&ent, (void *) k) != 0 && --lPos );

                if ( lPos == 0 ) // Not found
                    return 0;
                
            }

            return ((Node *) ent)->item;
        }

        else if ( h->type == CHAINING )
        {
            // Find the node 
            // We must pass the node address size, not the key size because search expect a node type, not a key
            // However the comparison function can compare a node with a key 
            if ( (lPos = llist_search((List *) ent, (void *) k, sizeof(Node *))) == -1 )
                return NULL; // Not found

            // Get the node from the list            
            ent = llist_getitemAt((List *) ent, lPos);

            // We store the address of the node in the list, so we have to deref as follows
            ent = *(void **) ent;

            return ((Node *) ent)->item;
        }
    }

    return NULL;
}

int hash_delete(Hash *h, Key *k)
{
    void **temp;
    void *ent;
    size_t hash, lPos;

    // Calculate the hash
    hash = key_hash(k, h->lMaxSize);

    // Find the target entry
    if ( ent = h->data[hash] )
    {
        if ( h->type == REPLACEMENT )
        {
            free( ent );
            h->data[hash] = NULL;
            h->lSize--;
            
            return 1;
        }

        else if ( h->type == OPEN_ADDRESSING )
        {
            // Pointing now to the suitable entry
            temp = h->data + hash;

            lPos = hash;
            // Find the target node
            do {
                ent = h->data[ lPos ];
                
                if ( ent && node_compare(&ent, (void *) k) == 0 )
                    break;

            } while ( ++lPos != h->lMaxSize );
            
            
            // If the node was not on the right
            if ( lPos == h->lMaxSize )
            {
                // Check if we were search from the beginning
                if ( hash == 0 )
                    return 0;

                // Pointing now to the suitable entry
                temp = h->data + hash;

                lPos = hash;

                do {
                    ent = *( --temp );
                } while ( node_compare(&ent, (void *) k) != 0 && --lPos );

                if ( lPos == 0 ) // Not found
                    return 0;
                
            }

            free( ent );
            ( *temp ) = NULL;
            h->lSize--;

            return 1;
        }

        else if ( h->type == CHAINING )
        {
            size_t lIdx;

            // Find the node
            if ( (lIdx = llist_search((List *) ent, (void *) k, sizeof(Node *))) == -1 )
                return 0; // We couldn't find the node
            
            // Delete the node from the list
            if ( ! llist_deleteAt((List *) ent, lIdx) )
                return 0; // Something goes wrong when deleting the node from the list

            // If the list becomes empty, we have to cleanup the list and mark this entry as unused
            if ( llist_empty((List *) ent) )
            {
                llist_cleanup( (List **) &ent );
                h->data[hash] = NULL;
            }

            h->lSize--;

            return 1;
        }

    }

    return 0;
}

int hash_next(Hash *h, size_t *lPos, Key **k, Item **i)
{
    void *entry;
    Node *node;

    // Check whether the given position is in the expected range or not
    if ( *lPos < 0 || *lPos >= h->lMaxSize )
        return 0;

    // Find the next available entry
    if ( ! (entry = h->data[ *lPos ]) )
    {
        do {
            // Check if we reach the end of the table
            if ( *lPos == h->lMaxSize )
                goto FAIL;

            entry = h->data[ ++(*lPos) ];
        } while ( ! entry );
    }

    if ( h->type == REPLACEMENT || h->type == OPEN_ADDRESSING )
    {
        *k = ( (Node *) entry )->key;
        *i = ( (Node *) entry )->item;

        // Next position 
        ( *lPos )++;
        
        return 1;
    }

    else if ( h->type == CHAINING )
    {   

        // Get current node
        if ( node = *(Node **) llist_getitemAt((List *) entry, h->lNextItemIdx) )
        {

            *k = node->key;
            *i = node->item;

            // Set next item index    
            h->lNextItemIdx++;

            // If the next item reachs the end of the list, we have to resotre it to zero and jump on the next entry
            if ( h->lNextItemIdx == llist_size((List *) entry) )
            {
                h->lNextItemIdx = 0;
                ( *lPos )++;
            }

            return 1;
        }
        
    }

FAIL:
    // Failed to get the node data
    *k = NULL;
    *i = NULL;

    return 0;
}

void hash_print(Hash *h)
{
    Item *pItem = NULL;
    Key *pKey = NULL;
    size_t lPos = 0;

    puts("{");

    while ( hash_next(h, &lPos, &pKey, &pItem) )
    {
        printf("\t");
        pKey->print( pKey->data );
        printf(": ");
        pItem->print( pItem->data );
        printf(",  // ( 0x%X )\n", key_hash(pKey, h->lMaxSize));
    }

    puts("}");
}

void hash_destroy(Hash **h)
{
    void **temp;
    Item *pItem = NULL;
    Key *pKey = NULL;
    size_t lPos = 0;

    // Destroy all keys and items
    while ( hash_next(*h, &lPos, &pKey, &pItem) )
    {
        key_destroy( &pKey );
        item_destroy( &pItem );
    }

    temp = (*h)->data;

    // Deallocate all entries
    while ( (*h)->lMaxSize-- )
    {
        if ( *temp )
        {
            if ( (*h)->type == CHAINING )
                llist_cleanup( (List **) temp );

            else
                node_destroy( (Node **) temp );
        }

        // Next entry
        temp++;
    }

    free( (*h)->data );
    free( *h );
    ( *h ) = NULL;
}