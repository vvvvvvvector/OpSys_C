#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int numbers[10] = {1, 1, 1, 1, 1, 2, 2, 2 ,2, 2};

void* func(void *arg){
    int index = *(int*)arg;
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[index + i];

    }
    printf("Local sum: %d\n", sum);
    *(int*)arg = sum;
    return arg;
}

int main(){
    pthread_t th[2];
    int sum = 0;

    for (int i = 0; i < 2; ++i) {
        int *arg = malloc(sizeof(int));
        *arg = i * 5;
        if (pthread_create(th + i, NULL, func, arg)) {
            perror("Creating thread error\n");
            _exit(1);
        }
    }

    for (int i = 0; i < 2; ++i) {
        int *result_from_thread;
        if (pthread_join(th[i], (void**)&result_from_thread)) {
             perror("Ending thread error\n");
            _exit(1);
        }
        sum += *result_from_thread;
        free(result_from_thread);
    }

    printf("result sum: %d\n", sum);
    
    return 0;
}