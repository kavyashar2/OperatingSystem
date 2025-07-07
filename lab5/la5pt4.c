// Name: Kavya Sharma
// Date: 10/23/204
// Title: Lab5 - Part 3
// Description: Producer-Consumer problem solved using a mutex lock

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NTHREADS 10

pthread_t threads[NTHREADS];
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
pthread_mutex_t lock;
pthread_cond_t full, empty;

void *producer(void *arg)
{
    while (1)
    {
        int item = rand() % 100;
        printf("Produced item %d\n", item);

        pthread_mutex_lock(&lock);
        while ((in + 1) % BUFFER_SIZE == out)
        {
            pthread_cond_wait(&empty, &lock);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        while (in == out)
        {
            pthread_cond_wait(&full, &lock);
        }

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("\tConsumed item %d\n", item);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

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

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}
