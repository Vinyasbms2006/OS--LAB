#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Pick left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork %d\n", id, id);

        // Pick right fork
        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked up right fork %d\n", id, (id + 1) % N);

        // Eat
        printf("Philosopher %d is eating\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d has finished eating\n", id);

        sleep(1);
    }
}

int main()
{
    pthread_t ph[N];
    int i, ids[N];

    // Initialize semaphores
    for (i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (i = 0; i < N; i++)
    {
        pthread_join(ph[i], NULL);
    }

    return 0;
}
