#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 5;

void *func(void *arg){
    for(int i = 0; i < 50; ++i){
        counter++;
    }
    return 0;
}

int main(){
    pthread_t thread1, thread2;
    
    if(pthread_create(&thread1, NULL, func, NULL)){
        perror("Blad tworzenia watku\n");
        _exit(1);
    }
    if(pthread_create(&thread2, NULL, func, NULL)){
        perror("Blad tworzenia watku\n");
        _exit(1);
    }

    void *result;

    if ( pthread_join ( thread1, &result ) ) {
        perror("Blad tworzenia watku 1\n");
        _exit(1);
    }
    if ( pthread_join ( thread2, &result ) ) {
        perror("Blad tworzenia watku 2\n");
        _exit(1);
    }

    printf("counter result = %d\n", counter);
    
    return 0;
}