#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int zmienna = 0;

pthread_mutex_t mutex;

void* inkrementuj(void* arg) {
    printf("Thread start...\n");
    // mutex zalozony
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 100000; ++i) {
        zmienna++;
    }
    pthread_mutex_unlock(&mutex);
    // mutex zdjety
    printf("Done...\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    char *end = NULL;
    int n = strtol(argv[1], &end, 0);

    pthread_t th[n];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < n; i++) {
        if (pthread_create(&th[i], NULL, inkrementuj, NULL)) {
           perror("Failed to creat thread\n");
           _exit(1);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Failed to join thread\n");
            _exit(1);
        }
    }
    
    pthread_mutex_destroy(&mutex);
    
    printf("Wartosc zmiennej po inkrementacji: %d\n", zmienna);
    printf("Oczekiwana wartosc zmiennej dla %d watkow: %d\n", n, n * 100000);
    
    return 0;
}