// Name: Kavya Sharma
// Date: 10/23/204
// Title: Lab5 - Part 3
// Description: Producer-Consumer problem solved using semaphores

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define NTHREADS 10
#define BUFFER_SIZE 10

pthread_t threads[NTHREADS];
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t *lock;
sem_t *empty;
sem_t *full;

void *producer(void *arg)
{
    while (1)
    {
        int item = rand() % 100;
        printf("Produced item %d\n", item);

        sem_wait(empty);
        sem_wait(lock);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(lock);
        sem_post(full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(full);
        sem_wait(lock);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("\tConsumed item %d\n", item);

        sem_post(lock);
        sem_post(empty);

        sleep(1);
    }
    return NULL;
}

int main()
{
    lock = sem_open("lock", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("full", O_CREAT, 0644, 0);

    for (int i = 0; i < NTHREADS / 2; i++)
    {
        pthread_create(&threads[i], NULL, producer, NULL);
    }
    for (int i = NTHREADS / 2; i < NTHREADS; i++)
    {
        pthread_create(&threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_unlink("lock");
    sem_unlink("empty");
    sem_unlink("full");

    return 0;
}
