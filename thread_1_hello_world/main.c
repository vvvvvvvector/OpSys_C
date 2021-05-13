#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* hello_world(void *arg){
    char *s = (char*)arg;
    printf("Hello %s!\n", s);
    return 0;
}

int main(int argc, char *argv[]){
    pthread_t hello_world_thread;
    if(pthread_create(&hello_world_thread, NULL, hello_world, (void*)argv[1])){
        perror("blad tworzenia");
        _exit(1);
    }
    if(pthread_join(hello_world_thread, NULL)){ // wait for thread end
        perror("błąd w kończeniu wątku\n");
        _exit(1);
    }
    printf("wyjscie z watka glownego\n");
    return 0;
}