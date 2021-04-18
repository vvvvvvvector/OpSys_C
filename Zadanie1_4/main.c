#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    printf("main process id: %d\n", getpid());
    int id = fork();
    if(id == 0){
        //printf("current ID: %d, parent ID: %d\n", getpid(), getppid());
        if(fork() == 0){
            printf("1 child ID: %d, parent ID: %d\n", getpid(), getppid());
        } else {
            wait(NULL);
            printf("2 child ID: %d, parent ID: %d\n", getpid(), getppid());
        }
    } else {
        wait(NULL);
        printf("current ID: %d, parent ID: %d\n", getpid(), getppid());
    }
    return 0;
}
