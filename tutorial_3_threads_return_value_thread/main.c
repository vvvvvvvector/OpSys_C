#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* roll_dice(){
    int *value = malloc(sizeof(int));
    *value = (rand() % 6) + 1;
    return (void*)value;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    pthread_t th;

    if (pthread_create(&th, NULL, roll_dice, NULL)) {
        perror("Failed to creat thread\n");
        _exit(1);
    }

    int *p_result;

    if (pthread_join(th, (void**)&p_result)) { 
        perror("Failed to join thread\n");
        _exit(1);
    }

    printf("Returned value = %d\n", *p_result);
    free(p_result);
    
    return 0;
}