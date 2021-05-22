#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine(){
    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&th[i], NULL, routine, NULL)) {
            perror("Creating thread error\n");
            _exit(1);
        } 
        printf("Thread %d has started\n", i + 1);
    }

    for (int i = 0; i < 4; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Ending thread error\n");
            _exit(1);
        }
        printf("Thread %d has finished execution\n", i + 1);
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    
    return 0;
}