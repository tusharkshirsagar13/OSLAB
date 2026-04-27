#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Producer function
void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100;  // produce an item

        sem_wait(&empty);     // wait if buffer is full
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);      // signal that buffer has new item

        sleep(1);
    }
}

// Consumer function
void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);      // wait if buffer is empty
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);     // signal that buffer has space

        sleep(2);
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // initially empty slots
    sem_init(&full, 0, 0);            // initially no items

    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Join threads
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}