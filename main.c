#include "restaurant_system.h"

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
	pthread_mutex_t mutex;
	sem_t *order_place_sem, *order_cook_sem, *order_serve_sem;

	sem_init(&order_serve_sem, 0, 3); /*  Limit of 3 orders being served at once */

	sem_t *order_place_sem = sem_open("order_place_sem", O_CREAT, 0644, 5);
	/* Allow up to 5 customers to place orders simultaneously */
	/* The number 0644 in the context of the sem_open function or
	/*other Unix-like system calls represents file permissions in an octal (base-8) notation. */
	if (order_place_sem == SEM_FAILED)
	{
		perror("Failed to open semaphore");
		exit(EXIT_FAILURE);
	}

	sem_t *order_cook_sem = sem_open("order_cook_sem", O_CREAT, 0644, 3);
	/* Limit of 3 orders being cooked at once */
	if (order_cook_sem == SEM_FAILED)
	{
		perror("Failed to open semaphore");
		exit(EXIT_FAILURE);
	}

	sem_t *order_serve_sem = sem_open("order_serve_sem", O_CREAT, 0644, 3);
	/* Limit of 3 orders being served at once */
	if (order_serve_sem == SEM_FAILED)
	{
		perror("Failed to open semaphore");
		exit(EXIT_FAILURE);
	}

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
	sem_close(order_place_sem);
	sem_unlink("order_place_sem");

	sem_close(order_cook_sem);
	sem_unlink("order_cook_sem");

	sem_close(order_serve_sem);
	sem_unlink("order_serve_sem");

	pthread_mutex_destroy(&mutex);

	return (0);
}
