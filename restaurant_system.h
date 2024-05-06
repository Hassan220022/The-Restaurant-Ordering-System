#ifndef RESTAURANT_SYSTEM_H
#define RESTAURANT_SYSTEM_H

#include <fcntl.h>	  /* For O_CREAT, etc.*/
#include <fcntl.h>	  /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <stdbool.h>  /* For bool type */
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

/* The volatile keyword prevents the compiler from applying certain */
/* types of optimization to the variable it decorates because it might */
/* change at any time—outside the control of the current code block. */
/* This is particularly important */

extern volatile bool keepRunning = true;

/* Queue for orders */
extern int order_queue[MAX_ORDERS];
extern int order_count = 0;

/* Mutex for critical section */
extern pthread_mutex_t mutex;

/* Function prototypes */
void *customer(void *);
void *chef(void *);
void *waiter(void *);

#endif /* RESTAURANT_SYSTEM_H */
