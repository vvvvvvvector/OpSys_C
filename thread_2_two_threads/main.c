#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *print_message_func(void *arg){
    char *s = (char*)arg;
    printf("%s\n", s);
    return 0;
}

int main(){
    pthread_t thread_1;
    pthread_t thread_2;

    const char *message_1 = "Thread 1";
    const char *message_2 = "Thread 2";

    if(pthread_create(&thread_1, NULL, print_message_func, (void*)message_1)){
        perror("błąd przy tworzeniu wątku 1\n");
        _exit(1);
    }
    if (pthread_join(thread_1, NULL)) {
		perror("błąd w kończeniu wątku 1\n");
		_exit(1);
	}
    if(pthread_create(&thread_2, NULL, print_message_func, (void*)message_2)){
        perror("błąd przy tworzeniu wątku 2\n");
        _exit(1);
    }
    if (pthread_join(thread_2, NULL)) {
		perror("błąd w kończeniu wątku 2\n");
		_exit(1);
	}
    
    printf("koniec programu\n");
    return 0;
}