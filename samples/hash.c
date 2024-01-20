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

int main()
{
    Hash *htable;
    Key *pKey;
    void *pData;
    int nKey, nValue, nRet;
    size_t lMaxSize = 10;

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
    {
        printf("key %d doesn't exist in the table\n", nKey);
    }
    // 4- Destroy the key
    key_destroy( &pKey );

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
        printf("\nhash[%d] = %d\n", nKey, *(int *) pData);
    else
        printf("\nKey %d doesn't exist in the hashtable\n", nKey);
    // 4- Destroy the key
    key_destroy( &pKey );

    nRet = EXIT_SUCCESS;

LEAVE:
    // Deallocate the table
    hash_destroy( &htable );

    return nRet;
}