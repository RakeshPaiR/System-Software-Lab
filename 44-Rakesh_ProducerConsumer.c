#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
  
 
 
#define SIZE 10
#define NUMB_THREADS 10
#define PRODUCER_LOOPS 2
#define CONSUMER_LOOPS 2
  
#define TRUE 1
#define FALSE 0
 
typedef int buffer_t;
buffer_t buffer[SIZE];
int buffer_index;
  
pthread_mutex_t buffer_mutex;
sem_t full_sem;
sem_t empty_sem;

void insertbuffer(buffer_t value) {
    if (buffer_index < SIZE) {
        buffer[buffer_index++] = value;
    } else {
        printf("Buffer overflow\n");
    }
}
  
buffer_t dequeuebuffer() {
    if (buffer_index > 0) {
        return buffer[--buffer_index];
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}
  
  
int isempty() {
    if (buffer_index == 0)
        return TRUE;
    return FALSE;
}
  
int isfull() {
    if (buffer_index == SIZE)
        return TRUE;
    return FALSE;
}
 
void *producer2(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < PRODUCER_LOOPS) {
        sleep(rand() % 10);
        value = rand() % 100;
        pthread_mutex_lock(&buffer_mutex);
        do {
            pthread_mutex_unlock(&buffer_mutex);
            sem_wait(&full_sem);

            pthread_mutex_lock(&buffer_mutex);
        } while (isfull());
        insertbuffer(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_sem);
        printf("Producer %d added %d to buffer\n", thread_numb, value);
    }
    pthread_exit(0);
}
  
void *consumer2(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < PRODUCER_LOOPS) {
        pthread_mutex_lock(&buffer_mutex);
        do {
            pthread_mutex_unlock(&buffer_mutex);
            sem_wait(&empty_sem);
            pthread_mutex_lock(&buffer_mutex);
        } while (isempty());
        value = dequeuebuffer(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_sem);
        printf("Consumer %d dequeue %d from buffer\n", thread_numb, value);
   }
    pthread_exit(0);
}
  
int main(int argc, int **argv) {
    buffer_index = 0;
  
    pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&full_sem, 0,SIZE);
    sem_init(&empty_sem,0,0);
    
    pthread_t thread[NUMB_THREADS];
    int thread_numb[NUMB_THREADS];
    int i;
    for (i = 0; i < NUMB_THREADS; ) {
        thread_numb[i] = i;
        pthread_create(thread + i, NULL,producer2,thread_numb + i);
        i++;
        thread_numb[i] = i;

        pthread_create(&thread[i], NULL, consumer2, &thread_numb[i]);
        i++;
    }
  
    for (i = 0; i < NUMB_THREADS; i++)
        pthread_join(thread[i], NULL);
  
    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&full_sem);
    sem_destroy(&empty_sem);
  
    return 0;
}