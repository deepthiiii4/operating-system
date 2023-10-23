#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
pthread_mutex_t x;
sem_t empty;
sem_t full;
int in = 0;
int out = 0;

void *producer(void *p_no)
{
    int data;
    for (int i = 0; i < MAX; i++)
    {
        data = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&x);
        buffer[in] = data;
        printf("producer %d: entered %d at %d index", *((int *)p_no), buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&x);
        sem_post(&full);
    }
}

void *consumer(void *c_no)
{
    sem_wait(&full);
    pthread_mutex_lock(&x);
    int data = buffer[out];
    printf("consumed %d: consumed %d at %d index", *((int *)c_no), data, out);
    out = (out + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&x);
    sem_post(&empty);
}

int main()
{
    pthread_t p_no[5], c_no[5];
    pthread_mutex_init(&x, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    int a[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&p_no[i], NULL, producer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&c_no[i], NULL, consumer, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(p_no[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(c_no[i], NULL);
    }
    pthread_mutex_destroy(&x);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
