#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// find /etc/ | head -3 | wc -c
int main(){
    int pid, pipe1[2], pipe2[2];

    if(pipe(pipe1) == -1){
        perror("blad tworzenia potoku 1");
        _exit(1);
    }

    if((pid = fork()) == 0){
        dup2(pipe1[1], 1);
        close(pipe1[1]);
        close(pipe1[0]);
        execlp("find", "find", "/etc/", NULL);
        perror("blad uruchomienia programu 1");
        _exit(1);
    }

    if(pipe(pipe2) == -1){
        perror("blad uruchomienia potoku 2");
        _exit(1);
    }

    if((pid = fork()) == 0){
        dup2(pipe1[0], 0);
        dup2(pipe2[1], 1);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        close(pipe2[0]);
        execlp("head", "head", "-3", NULL);
        perror("blad uruchomienia programu 2");
        _exit(1);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    
    if((pid = fork()) == 0){
        dup2(pipe2[0], 0);
        close(pipe2[0]);
        close(pipe2[1]);

        int file = open("file.txt", O_WRONLY | O_CREAT, 0777);
        dup2(file, STDOUT_FILENO);

        execlp("wc", "wc", "-c", NULL);
        perror("blad uruchomienia programu 3");
        _exit(1);
    }

    close(pipe2[0]);
    close(pipe2[1]);

    waitpid(pid, NULL, 0);
    
    return 0;
}