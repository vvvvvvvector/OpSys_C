#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* func(void *arg){
    int value = *((int*)arg);
    printf("%d ", value);
    //free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[10]; 

    for (int i = 0; i < 10; ++i) {
        //int *a = malloc(sizeof(int));
        //*a = i;
        if (pthread_create(&th[i], NULL, func, primes + i)) {
            perror("Failed to create thread\n");
            _exit(1);
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (pthread_join(th[i], NULL)) {
            perror("Failed to join thread\n");
            _exit(1);
        }
    }
    
    return 0;
}