#include <bits/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <string.h>

int main(){
    int fd[2];

    if(pipe(fd) == -1){
        perror("blad tworzenia potoku\n");
        _exit(1);
    }

    int pid1 = fork();
    if(pid1 == -1){
        perror("blad tworzenia procesu\n");
        _exit(1);
    }

    if(pid1 == 0){
        close(fd[0]);
        char message[31];
        sprintf(message, "Moj PID to %d\n", getpid());
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
    } else {
        int pid2 = fork();

        if(pid2 == -1){
            perror("blad tworzenia procesu\n");
            _exit(1);
        }
        
        if(pid2 == 0){
            close(fd[1]);
            char readBuf[31];
            read(fd[0], readBuf, sizeof(readBuf));
            printf("%sA moj PID to %d\n",readBuf, getpid());
            close(fd[0]);
        }  else {
            wait(NULL);
        }
    }
        
    return 0;
}