#include "restaurant_system.h"

/**
 * customer - Simulates a customer's behavior in a restaurant ordering system.
 * @param: A void pointer that represents the customer's ID.
 *
 * This function is designed to run in a separate thread for each customer. It
 * places an order if the current `order_count` is less than `MAX_ORDERS`, and
 * manages access to the shared `order_queue` and `order_count` variables using
 * a mutex and semaphore.
 *
 * Return: NULL
 */
void *customer(void *param)
{
	int id = (int)(intptr_t)param;

	sem_wait(&order_place_sem);
	pthread_mutex_lock(&mutex);
	if (order_count < MAX_ORDERS)
	{
		order_queue[order_count++] = id;
		printf("Customer %d placed an order\n", id);
	}
	pthread_mutex_unlock(&mutex);
	sem_post(&order_place_sem);
	return (NULL);
}

/**
 * chef - Simulates a chef's behavior in a restaurant ordering system.
 * @param: A void pointer that represents the chef's ID.
 *
 * This function is designed to run in a separate thread for each chef. It
 * prepares orders placed by customers, managing access to the shared
 * order queue and order count variables using a mutex and semaphore.
 *
 * Return: NULL
 */
void *chef(void *param)
{
	int id = *((int *)param);

	while (keepRunning)
	{
		/* Lock mutex before accessing shared resource */
		pthread_mutex_lock(&mutex);
		if (order_count > MAX_ORDERS)
		{
			printf("Chef %d is cooking. Orders left: %d\n", id, order_count);
			/* Decrement the count of orders, simulating cooking an order */
			order_count--;
			/* Unlock mutex after accessing shared resource */
			pthread_mutex_unlock(&mutex);

			sleep(2);

			if (order_count == 0)
			{
				/* Set keepRunning to false when there are no more orders to process */
				keepRunning = 0;
			}
		}
		else
		{
			pthread_mutex_unlock(&mutex);
			sleep(1); /* Sleep to avoid tight looping when there are no orders */
		}
	}

	printf("Chef %d stopping.\n", id);
	return (NULL);
}

/**
 * waiter - Simulates a waiter's behavior in a restaurant ordering system.
 * @param: A void pointer that represents the waiter's ID.
 *
 * This function is designed to run in a separate thread for each waiter. It
 * serves orders prepared by chefs, managing access to the shared order queue
 * and order count variables using a mutex and semaphore.
 *
 * Return: NULL
 */
void *waiter(void *param)
{
	int id = (int)(intptr_t)param;

	while (1)
	{
		sem_wait(&order_serve_sem);
		printf("Waiter %d is serving an order\n", id);
		sleep(1); /* Simulate serving time */
		printf("Waiter %d has served an order\n", id);
		sem_post(&order_serve_sem);
		sleep(1);
	}
	return (NULL);
}
