#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full;
pthread_mutex_t mutex;

// Producer function
void *producer(void *arg) {
    int item;

    for (int i = 0; i < 10; i++) {
        item = rand() % 100;

        sem_wait(&empty);              // wait(empty)
        pthread_mutex_lock(&mutex);    // wait(mutex)

        buffer[in] = item;
        printf("Producer produced %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // signal(mutex)
        sem_post(&full);               // signal(full)

        sleep(1);
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    int item;

    for (int i = 0; i < 10; i++) {

        sem_wait(&full);               // wait(full)
        pthread_mutex_lock(&mutex);    // wait(mutex)

        item = buffer[out];
        printf("Consumer consumed %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // signal(mutex)
        sem_post(&empty);              // signal(empty)

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    // Initialize
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Destroy
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
