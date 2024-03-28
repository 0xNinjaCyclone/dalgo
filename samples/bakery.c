/*
    Lamport's bakery Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 27-3-2024/09:38PM
    Compile     => gcc -I../Algo/ ../Algo/bakery.c bakery.c -o bakery -pthread
*/

#include "bakery.h"
#include <stdio.h>
#include <unistd.h>

#define NUMOFTHREADS 5


BakeryLock *g_pLock;

void *critical_task(void *ptr)
{
    bakery_register(g_pLock, *(pthread_t *) ptr);
    bakery_lock(g_pLock, *(pthread_t *) ptr);
    printf("critical_task() called by %lu\n", *(unsigned long *) ptr);

    // CRITICAL SECTION (BEGINNING)

    for (int ctr = 0; ctr < 20; ctr++)
    {
        printf("This is a critical section executed by %lu\n", *(unsigned long *) ptr);
        usleep(20000);
    }

    // CRITICAL SECTION (ENDING)

    printf("critical_task() called by %lu has finished\n\n", *(unsigned long *) ptr);
    bakery_unlock(g_pLock, *(pthread_t *) ptr);
}

int main()
{
    pthread_t thrds[NUMOFTHREADS] = { 0 };

    if ( !(g_pLock = bakery_init(NUMOFTHREADS)) )
        return EXIT_FAILURE;

    for ( __uint8_t unIdx = 0; unIdx < NUMOFTHREADS; unIdx++ )
        pthread_create(&thrds[unIdx], NULL, critical_task, &thrds[unIdx]);

    for ( __uint8_t unIdx = 0; unIdx < NUMOFTHREADS; unIdx++ )
        pthread_join(thrds[unIdx], NULL);

    bakery_cleanup( &g_pLock );
    return EXIT_SUCCESS;    
}