/*
    Lamport's bakery Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 27-3-2024/08:58PM
*/

#include "bakery.h"

BakeryLock *bakery_init(__uint8_t unMaxThreads)
{
    BakeryLock *pLock;

    if ( pLock = malloc(sizeof(BakeryLock)) )
    {
        pLock->unMaxThreads = unMaxThreads;
        pLock->unNumberOfThreads = 0;

        if ( pLock->instances = calloc(pLock->unMaxThreads, sizeof(BakeryThread *)) )
            return pLock;

        free( pLock );
    }

    return NULL;
}

bool bakery_register(BakeryLock *pLock, pthread_t id)
{
    BakeryThread *pThrdInstance;

    if ( pLock->unNumberOfThreads < pLock->unMaxThreads && (pThrdInstance = malloc(sizeof(BakeryThread))) )
    {
        pThrdInstance->id = id;
        pThrdInstance->unIndex = pLock->unNumberOfThreads++;
        pThrdInstance->bFlag = false;
        pThrdInstance->unTicket = 0;
        pLock->instances[ pThrdInstance->unIndex ] = pThrdInstance;
        return true;
    }

    return false;
}

__int8_t bakery_lock(BakeryLock *pLock, pthread_t id)
{
    BakeryThread *pThrdInstance = NULL;
    __uint16_t unTicket = 0;
    __int8_t nRet = 0;

    // Find thread instance by id
    for ( __uint8_t unIdx = 0; unIdx < pLock->unNumberOfThreads; unIdx++ )
        if ( pLock->instances[unIdx]->id == id )
        {
            pThrdInstance = pLock->instances[ unIdx ];
            break;
        }

    if ( pThrdInstance )
    {
        // Says to other threads: You had better wait, motherf*ckers! 
        pThrdInstance->bFlag = true;

        // Get a ticket
        for ( __uint8_t unIdx = 0; unIdx < pLock->unNumberOfThreads; unIdx++ )
            if ( unIdx != pThrdInstance->unIndex && pLock->instances[unIdx]->unTicket > unTicket )
                unTicket = pLock->instances[unIdx]->unTicket;
            
        // The largest ticket plus one ( max(tickets) + 1 )
        pThrdInstance->unTicket = ++unTicket;

        // Says to other threads: Now you can complete your task.
        pThrdInstance->bFlag = false;

        for ( __uint8_t unIdx = 0; unIdx < pLock->unNumberOfThreads; unIdx++ )
        {
            if ( unIdx != pThrdInstance->unIndex )
            {
                // Someone picks a ticket, so we have to wait
                while ( pLock->instances[unIdx]->bFlag );

                // We cannot enter a critical section if someone entered before us and did not complete
                while ( 
                    pLock->instances[unIdx]->unTicket != 0 && (
                        pLock->instances[unIdx]->unTicket < pThrdInstance->unTicket ||
                        ( pLock->instances[unIdx]->unTicket == pThrdInstance->unTicket && unIdx < pThrdInstance->unIndex )
                    )
                )
                    nRet = 1; // Busy wait
            }
        }

        return nRet;
    }

    return -1;
}

__int8_t bakery_unlock(BakeryLock *pLock, pthread_t id)
{
    BakeryThread *pThrdInstance = NULL;
    __int8_t nRet = 1;

    // Find thread instance by id
    for ( __uint8_t unIdx = 0; unIdx < pLock->unNumberOfThreads; unIdx++ )
        if ( pLock->instances[unIdx]->id == id )
        {
            pThrdInstance = pLock->instances[ unIdx ];
            break;
        }

    if ( pThrdInstance )
    {
        if ( pThrdInstance->unTicket != 0 )
            nRet = pThrdInstance->unTicket = 0;

        return nRet;
    }

    return -1;
}

void bakery_cleanup(BakeryLock **pLock)
{
    // Get rid of all thread instances
    for ( BakeryThread **tmp = (*pLock)->instances; (*pLock)->unNumberOfThreads--; free( *tmp++ ) );

    // Free the lock
    free( *pLock );

    // To avoid pointer dangling
    ( *pLock ) = NULL;
}