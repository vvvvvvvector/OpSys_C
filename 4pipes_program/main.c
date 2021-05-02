#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//ps -laef | cut -c 48- | sort | uniq -c | sort -n
int main(){
    int pid, pipe1[2], pipe2[2], pipe3[2], pipe4[2];

    if(pipe(pipe1) == -1){
        perror("blad tworzenia potoku 1");
        _exit(1);
    }

    if((pid = fork()) == 0){
        dup2(pipe1[1], 1);
        close(pipe1[1]);
        close(pipe1[0]);
        execlp("ps", "ps", "-laef", NULL);
        perror("blad uruchomienia programu 1");
        _exit(1);
    }

    if(pipe(pipe2) == -1){
        perror("blad tworzenia potoku 2");
        _exit(1);
    }

    if((pid = fork()) == 0){
        dup2(pipe1[0], 0);
        dup2(pipe2[1], 1);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        close(pipe2[0]);
        execlp("cut", "cut", "-c", "48-", NULL);
        perror("blad uruchomienia programu 2");
        _exit(1);
    }

    close(pipe1[0]);
    close(pipe1[1]);

    if(pipe(pipe3) == -1){
        perror("blad tworzenia potoku 3");
        _exit(1);
    }

    if((pid = fork()) == 0){
        dup2(pipe2[0], 0);
        dup2(pipe3[1], 1);
        close(pipe2[0]);
        close(pipe2[1]);
        close(pipe3[1]);
        close(pipe3[0]);
        execlp("sort", "sort", NULL);
        perror("blad uruchomienie programu 3");
        _exit(1);
    }

    close(pipe2[0]);
    close(pipe2[1]);

    if(pipe(pipe4) == -1){
        perror("blad tworzenia potoku 3");
        _exit(1);
    }

    if((pid = fork()) == 0){
        dup2(pipe3[0], 0);
        dup2(pipe4[1], 1);
        close(pipe3[0]);
        close(pipe3[1]);
        close(pipe4[1]);
        close(pipe4[0]);
        execlp("uniq", "uniq", "-c", NULL);
        perror("blad uruchomienia programu 4");
        _exit(1);
    }

    close(pipe3[0]);
    close(pipe3[1]);

    if((pid = fork()) == 0){
        dup2(pipe4[0], 0);
        close(pipe4[0]);
        close(pipe4[1]);

        int file = open("file.txt", O_WRONLY | O_CREAT, 0777);
        dup2(file, STDOUT_FILENO);

        execlp("sort", "sort", "-n", NULL);
        perror("blad uruchomienia programu 5"); 
        _exit(1);
    }

    close(pipe4[0]);
    close(pipe4[1]);

    waitpid(pid, NULL, 0);
    
    return 0;
}