#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 8

// this semaphores are keep tracking how many element we have in the buffer
sem_t semFull;
sem_t semEmpty;

pthread_mutex_t mutex_buffer;

int buffer[10];
int count = 0;

void* producer(void* args) {
    while (1) {
        // produce
        int x = rand() % 100; // 0 - 99
        sleep(1); // producing is taking 1 second

        sem_wait(&semEmpty); // if semEmpty == 0 -> it means that there are no slots. It means that we should wait here
        pthread_mutex_lock(&mutex_buffer);
        // add to the buffer
        //if (count < 10) {
        buffer[count] = x;
        count++;
        //} else {
        //    printf("Skipped %d!\n", x);
        //}
        pthread_mutex_unlock(&mutex_buffer);
        sem_post(&semFull); // if we add an element, we should increment semaphore that represents the number of elements
    };
    return NULL;
}

void* consumer(void* args) {
    while (1) {
        //int y = -1;
        int y;
        
        // 4real semFull represents the count variable
        sem_wait(&semFull); // semFull == 0 -> here we should wait until that at least 1 element in the buffer
        pthread_mutex_lock(&mutex_buffer);
        // remove from the buffer
        //if (count  > 0) { 
        y = buffer[count - 1];
        count--;
        //}
        pthread_mutex_unlock(&mutex_buffer);
        sem_post(&semEmpty); // we should tell that an empty slot is available -> we can add new element in buffer

        // consume
        printf("Got a number: %d\n", y); // prints -1 if nothing was taken from the buffer
        //sleep(1); // consumption is taking 1 second
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutex_buffer, NULL);

    sem_init(&semEmpty, 0, 10); // 0 because we not sharing it between processes, we have 1 process and 2 threads
    // 10 - number of slots that are available at the begining
    sem_init(&semFull, 0, 0); // 0 because we not sharing it between processes, we have 1 process and 2 threads
    // 0 - number of slots that are available if buffer is full

    for (int i = 0; i < THREAD_NUM; ++i) {
        if (i > 0) {
            if (pthread_create(&th[i], NULL, producer, NULL) != 0) {
                perror("failed to create producer thread!\n");
                _exit(1);
            }
        } else {
            if (pthread_create(&th[i], NULL, consumer, NULL) != 0) {
                perror("failed to create consumer thread!\n");
                _exit(1);
            }
        }
    }

    for (int i = 0; i < THREAD_NUM; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Failed to join thread\n");
            _exit(1);
        }
    }

    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    
    pthread_mutex_destroy(&mutex_buffer);
    
    return 0;
}