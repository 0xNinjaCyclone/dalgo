/*
    Peterson Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 24-3-2024
*/

#include "peterson.h"

PetersonLock *peterson_init()
{
    PetersonLock *pLock;

    if ( pLock = malloc(sizeof(PetersonLock)) )
    {
        pLock->unNumberOfThreads = 0;
        pLock->unTurn = 0;
        
        if ( pLock->instances = calloc(MAX_PETERSON_THREADS, sizeof(PetersonThread *)) )
            return pLock;

        free( pLock );
    }

    return NULL;
}

bool peterson_register(PetersonLock *pLock, pthread_t id)
{
    PetersonThread *pThrdInstance;

    if ( pLock->unNumberOfThreads >= MAX_PETERSON_THREADS )
        return false;

    if ( !(pThrdInstance = malloc(sizeof(PetersonThread))) )
        return false;

    pThrdInstance->id = id;
    pThrdInstance->unIndex = pLock->unNumberOfThreads++;
    pThrdInstance->bFlag = false;
    pLock->instances[ pThrdInstance->unIndex ] = pThrdInstance;
    return true;
}

__int8_t peterson_lock(PetersonLock *pLock, pthread_t id)
{
    PetersonThread *pThrdInstance = NULL;
    __int8_t nRet = 0;

    // Find the target thread by its id
    for ( __uint16_t unTargetThrdIdx = 0; unTargetThrdIdx < pLock->unNumberOfThreads; unTargetThrdIdx++ )
    {
        if ( pLock->instances[unTargetThrdIdx]->id == id )
        {
            pThrdInstance = pLock->instances[unTargetThrdIdx];
            break;
        }
    }


    if ( pThrdInstance )
    {
        // Indicates that the current thread has entered the critical section
        pThrdInstance->bFlag = true;

        // We don't have to block the thread as long as there is no other
        if ( pLock->unNumberOfThreads <= 1 )
            return 0;

        // Jump to the counterpart thread
        pThrdInstance = pLock->instances[ 1 - pThrdInstance->unIndex ];

        // unTurn eq to the counterpart thread index within the table
        pLock->unTurn = pThrdInstance->unIndex;

        // The condition looks pretty weird, so I encourage u to read 'Operating Systems Concepts' book ch5 to understand the logic
        while ( pThrdInstance->bFlag && pLock->unTurn == pThrdInstance->unIndex )
            nRet = 1; // Busy wait

        return nRet;
    }

    return -1;
}

__int8_t peterson_unlock(PetersonLock *pLock, pthread_t id)
{
    PetersonThread *pThrdInstance = NULL;

    // Find the target thread
    for ( uint16_t unIdx = 0; unIdx < pLock->unNumberOfThreads; unIdx++ )
        if ( pLock->instances[unIdx]->id == id )
        {
            pThrdInstance = pLock->instances[unIdx];
            break;
        }

    if ( pThrdInstance )
    {
        // Unlock the other thread
        if ( pThrdInstance->bFlag )
        {
            pThrdInstance->bFlag = false;
            return 0;
        }

        return 1;
    }

    return -1;
}

void peterson_cleanup(PetersonLock **pLock)
{
    // Get rid of all thread instances
    for ( PetersonThread **tmp = (*pLock)->instances; (*pLock)->unNumberOfThreads--; free( *tmp++ ) );

    // Free the lock
    free( *pLock );

    // To avoid pointer dangling
    ( *pLock ) = NULL;
}