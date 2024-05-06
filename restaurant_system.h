#ifndef RESTAURANT_SYSTEM_H
#define RESTAURANT_SYSTEM_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ORDERS 10

/* Semaphores */
extern sem_t order_place_sem;
extern sem_t order_cook_sem;
extern sem_t order_serve_sem;

/* Flag to control chef threads */
extern int keepRunning;

/* Queue for orders */
extern int order_queue[MAX_ORDERS];
extern int order_count;

/* Mutex for critical section */
extern pthread_mutex_t mutex;

/* Function prototypes */
void *customer(void *);
void *chef(void *);
void *waiter(void *);

#endif /* RESTAURANT_SYSTEM_H */
