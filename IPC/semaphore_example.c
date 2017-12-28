#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include "app_debug.h"

#define handle_error(en, msg) \
			do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

/* prototype for thread routine */
void handler(void *ptr);

sem_t mutex;
int counter;

int main()
{
	int i[2] = {1, 2};
	pthread_t thread_a;
	pthread_t thread_b;

	/* initialize mutex to 1 - binary semaphore */
	/* second param = 0 - semaphore is local */
	sem_init(&mutex, 0, 1);

	pthread_create(&thread_a, NULL, (void *)&handler, (void *)&i[0]);
	pthread_create(&thread_b, NULL, (void *)&handler, (void *)&i[1]);

	sleep(10);

	/* Trigger worker-thread exit. */
	if (pthread_cancel(thread_a) != 0)
		ERR("Thread cancel of \"thread_a\" failed.\n");
	if (pthread_cancel(thread_b) != 0)
		ERR("Thread cancel of \"thread_b\" failed.\n");

	pthread_join(thread_a, NULL);
	pthread_join(thread_b, NULL);

	/* Destroy semaphore after use. */
	sem_destroy(&mutex);

	/* exit */
	exit(0);
}

void handler(void *ptr)
{
	int x, s;
	x = *((int *)ptr);
	if ((s=pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL)) != 0)
		handle_error(s, "pthread_setcancelstate");
	sleep(1);
	if ((s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) != 0)
		handle_error(s, "pthread_setcancelstate");
	while (1) {
		printf("Thread %d: Waiting to enter critical region...\n", x);
		/* Acquire semaphore */
		sem_wait(&mutex);
		/* START CRITICAL REGION */
		printf("Thread %d: Now in critical region...\n", x);
		printf("Thread %d: Counter Value: %d\n", x, counter);
		printf("Thread %d: Incrementing Counter...\n", x);
		counter++;
		printf("Thread %d: New Counter Value: %d\n", x, counter);
		printf("Thread %d: Exiting critical region...\n", x);
		/* END CRITICAL REGION */
		/* Release semaphore or increment its count. */
		sem_post(&mutex);
		printf("Thread %d: sem_post done...\n", x);
		sleep(1);
	}
	pthread_exit(0);
}

