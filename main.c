#include "restaurant_system.h"

/* Semaphores */
sem_t order_place_sem;
sem_t order_cook_sem;
sem_t order_serve_sem;

/* Flag to control chef threads */
int keepRunning = 1;

/* Queue for orders */
int order_queue[MAX_ORDERS];
int order_count = 0;

/* Mutex for critical section */
pthread_mutex_t mutex;

/**
 * main - Entry point for the restaurant ordering system simulation.
 *
 * This function initializes semaphores and creates threads for customers,
 * chefs, and waiters. The semaphores control the number of simultaneous
 * orders that can be placed, cooked, and served.
 *
 * Return: 0 on successful execution.
 */
int main(void)
{
	pthread_t tid_customers[5];
	pthread_t tid_chefs[3];
	pthread_t tid_waiters[3];

	/* Initialize semaphores */
	sem_init(&order_place_sem, 0, 5); /* Allow up to 5 customers to place orders simultaneously */
	sem_init(&order_cook_sem, 0, 3);  /* Limit of 3 orders being cooked at once */
	sem_init(&order_serve_sem, 0, 3); /* Limit of 3 orders being served at once */

	/* Initialize mutex */
	pthread_mutex_init(&mutex, NULL);

	/* Create threads */
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&tid_customers[i], NULL, customer, (void *)(intptr_t)i);
	}
	for (int i = 0; i < 3; i++)
	{
		pthread_create(&tid_chefs[i], NULL, chef, (void *)(intptr_t)i);
	}
	for (int i = 0; i < 3; i++)
	{
		pthread_create(&tid_waiters[i], NULL, waiter, (void *)(intptr_t)i);
	}

	/* Wait for threads to finish */
	for (int i = 0; i < 5; i++)
	{
		pthread_join(tid_customers[i], NULL);
	}
	for (int i = 0; i < 3; i++)
	{
		pthread_join(tid_chefs[i], NULL);
	}
	for (int i = 0; i < 3; i++)
	{
		pthread_join(tid_waiters[i], NULL);
	}

	/* Destroy semaphores and mutex */
	sem_destroy(&order_place_sem);
	sem_destroy(&order_cook_sem);
	sem_destroy(&order_serve_sem);

	pthread_mutex_destroy(&mutex);

	return (0);
}
