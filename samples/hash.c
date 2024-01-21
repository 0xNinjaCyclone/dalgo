/*
    Hash Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 19-1-2024
    Compile     => gcc -I../DS/ -I../Algo/ ../Algo/helpers.c ../DS/llist.c ../DS/hash.c hash.c -o hash
*/

#include "hash.h"
#include "helpers.h"

int insert_int_node(Hash *htable, int nKey, int nValue)
{
    Key *pKey;
    Item *pItem;

    // Initialize a key instance from nKey 
    if ( !(pKey = key_new(&nKey, sizeof(int), IntPrint, IntCmp)) )
        return 0;

    // Initialize an item instance from nValue 
    if ( !(pItem = item_new(&nValue, sizeof(int), malloc, free, IntPrint, IntCmp)) )
        return 0;

    return hash_insert(htable, pKey, pItem);
}

int insert_str_node(Hash *htable, char *cpKey, char *cpValue)
{
    Key *pKey;
    Item *pItem;

    // Initialize a key instance from cpKey 
    if ( !(pKey = key_new(cpKey, strlen(cpKey) + 1, StrPrintA, StrCmpA)) )
        return 0;

    // Initialize an item instance from cpValue 
    if ( !(pItem = item_new(cpValue, strlen(cpValue) + 1, malloc, free, StrPrintA, StrCmpA)) )
        return 0;

    return hash_insert(htable, pKey, pItem);
}

int main()
{
    Hash *htable;
    Key *pKey;
    Item *pItem;
    void *pData;
    int nKey, nValue, nRet;
    size_t lMaxSize = 10, lPos = 0;

    nRet = EXIT_FAILURE;

    // Initialize a hash table
    if ( !(htable = hash_new(lMaxSize, CHAINING)) )
        return nRet;

    nKey = 10;
    nValue = 10;

    // Fill the hash table
    while ( lMaxSize-- )
    {
        // hashtable[ nKey ] = nValue
        if ( ! insert_int_node(htable, nKey, nValue) )
        {
            printf("Error when do (hashtable[%d] = %d)\n", nKey, nValue);
            goto LEAVE;
        }

        if ( lMaxSize % 5 == 0 )
            nKey += 15;

        nKey++;
        nValue += 10;
    }

    // Delete the item with key 10
    nKey = 10;
    // 1- build the key from its value
    pKey = key_new(&nKey, sizeof(int), IntPrint, IntCmp);
    // 2- Check if error occured
    if ( ! pKey ) goto LEAVE;
    // 3- Call delete function 
    if ( ! hash_delete(htable, pKey) )
        printf("key %d doesn't exist in the table\n", nKey);
    // 4- Destroy the key
    key_destroy( &pKey );

    // Insert a string node
    if ( ! insert_str_node(htable, "Name", "Abdallah") )
        puts("Failed to insert a string node");

    // Insert a node with a string key and a numerical value
    char cKey[] = "Number of nodes";
    // 1- Initialize a key instance from cKey 
    if ( !(pKey = key_new(cKey, sizeof(cKey), StrPrintA, StrCmpA)) )
        goto LEAVE;
    // 2- Initialize an item instance from the size of the table 
    if ( !(pItem = item_new(&htable->lSize, sizeof(size_t), malloc, free, ULongPrint, ULongCmp)) )
        goto LEAVE;
    // 3- Insert the node into the table
    if ( ! hash_insert(htable, pKey, pItem) )
        puts("Failed to insert the table size into the hash table");

    // Display the table
    hash_print( htable );

    // Get the item with key 31
    nKey = 31;
    // 1- build the key from its value
    pKey = key_new(&nKey, sizeof(int), IntPrint, IntCmp);
    // 2- Check if error occured
    if ( ! pKey ) goto LEAVE;
    // 3- Get the item by the key
    if ( pData = hash_get(htable, pKey) ) 
        printf("\n[hash_get] hash[%d] => %d\n\n", nKey, *(int *) pData);
    else
        printf("\nKey %d doesn't exist in the hashtable\n\n", nKey);
    // 4- Destroy the key
    key_destroy( &pKey );

    // Iterate over all nodes
    while ( hash_next(htable, &lPos, &pKey, &pItem) )
    {
        printf("[hash_next] htable[");
        pKey->print( pKey->data );
        printf("] => ");
        pItem->print( pItem->data );
        puts(""); // Newline
    }

    nRet = EXIT_SUCCESS;

LEAVE:
    // Deallocate the table
    hash_destroy( &htable );

    return nRet;
}