/*
    Peterson Sample
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 24-3-2024
    Compile     => gcc -I../Algo/ ../Algo/peterson.c peterson.c -o peterson -pthread
*/

#include "peterson.h"
#include <stdio.h>
#include <unistd.h>

PetersonLock *g_pLock;

void *critical_task(void *ptr)
{
    peterson_register(g_pLock, *(pthread_t *) ptr);
    peterson_lock(g_pLock, *(pthread_t *) ptr);
    printf("critical_task() called by %lu\n", *(unsigned long *) ptr);

    // CRITICAL SECTION (BEGINNING)

    for (int ctr = 0; ctr < 20; ctr++)
    {
        printf("This is a critical section executed by %lu\n", *(unsigned long *) ptr);
        usleep(20000);
    }

    // CRITICAL SECTION (ENDING)

    printf("critical_task() called by %lu has finished\n\n", *(unsigned long *) ptr);
    peterson_unlock(g_pLock, *(pthread_t *) ptr);
}

int main() {
    pthread_t thrd1, thrd2;

    if ( !(g_pLock = peterson_init()) )
        return EXIT_FAILURE;

    pthread_create(&thrd1, NULL, critical_task, &thrd1);
    pthread_create(&thrd2, NULL, critical_task, &thrd2);

    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);

    peterson_cleanup( &g_pLock );

    return EXIT_SUCCESS;
}