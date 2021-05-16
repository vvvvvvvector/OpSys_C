#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine(){
    printf("Test from threads\n");
    sleep(3);
    printf("Ending tread\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, routine, NULL)) {
        perror("creating thread 1 error\n");
        _exit(1);
    }    
    if (pthread_create(&t2, NULL, routine, NULL)) {
        perror("creating thread 2 error\n");
        _exit(1);
    }
    if (pthread_join(t1, NULL)) {
        perror("Ending thread 1 error\n");
        _exit(1);
    }
    if (pthread_join(t2, NULL)) {
        perror("Ending thread 2 error\n");
        _exit(1);
    }
    
    return 0;
}