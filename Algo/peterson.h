#ifndef _dalgo_peterson
#define _dalgo_peterson

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#define MAX_PETERSON_THREADS 2

typedef struct {
    pthread_t id;
    __uint8_t unIndex;
    bool bFlag;
} PetersonThread;

typedef struct {
    __uint8_t unTurn;
    __uint8_t unNumberOfThreads;
    PetersonThread **instances;
} PetersonLock;

PetersonLock *peterson_init();
bool peterson_register(PetersonLock *pLock, pthread_t id);
__int8_t peterson_lock(PetersonLock *pLock, pthread_t id);
__int8_t peterson_unlock(PetersonLock *pLock, pthread_t id);
void peterson_cleanup(PetersonLock **pLock);

#endif