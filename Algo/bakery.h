#ifndef _dalgo_bakery
#define _dalgo_bakery

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

typedef struct {
    pthread_t id;
    __uint8_t unIndex;
    bool bFlag;
    __uint16_t unTicket;
} BakeryThread;

typedef struct {
    __uint8_t unMaxThreads;
    __uint8_t unNumberOfThreads;
    BakeryThread **instances;
} BakeryLock;

BakeryLock *bakery_init(__uint8_t unMaxThreads);
bool bakery_register(BakeryLock *pLock, pthread_t id);
__int8_t bakery_lock(BakeryLock *pLock, pthread_t id);
__int8_t bakery_unlock(BakeryLock *pLock, pthread_t id);
void bakery_cleanup(BakeryLock **pLock);

#endif