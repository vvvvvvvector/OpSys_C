#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

int fuel = 0;
pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;

void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_fuel);
        fuel += 15;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutex_fuel);
        pthread_cond_signal(&cond_fuel); // conditon in while() loop might have changed
        sleep(1);
    }
    return NULL;   
}

void* car(void* arg) {
    pthread_mutex_lock(&mutex_fuel);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&cond_fuel, &mutex_fuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutex_fuel);
        // wait for signal on cond_fuel
        // pthread_mutex_lock(&mutex_fuel);
    }
    fuel -= 40;
    printf("Got fuel, now left... %d\n", fuel);
    pthread_mutex_unlock(&mutex_fuel);
    return NULL;
}

int main(){
    pthread_t th[2];
    pthread_mutex_init(&mutex_fuel, NULL);
    pthread_cond_init(&cond_fuel, NULL);

    for (int i = 0; i < 2; ++i) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, fuel_filling, NULL)) {
                 perror("Failed to creat thread\n");
                _exit(1);
            }
        } else {
            if (pthread_create(&th[i], NULL, car, NULL)) {
                 perror("Failed to creat thread\n");
                _exit(1);
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (pthread_join(th[i], NULL)) {
                 perror("Failed to join thread\n");
                _exit(1);
            }
    }
    
    pthread_mutex_destroy(&mutex_fuel);
    pthread_cond_destroy(&cond_fuel);
    
    return 0;
}