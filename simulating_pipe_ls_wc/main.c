#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int fd[2];
    
    if(pipe(fd) == -1){
        perror("Blad tworzenia potoku");
        exit(1);
    }
    
    int pid1 = fork();
    if(pid1 == -1){
        perror("Blad tworzenia procesu 1");
        exit(1);
    }
    
    if(pid1 == 0){
        //Child process 1(ls)
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execvp("ls", argv);
    }
    
    int pid2 = fork();
    if(pid2 == -1){
        perror("Blad tworzenia procesu 2");
        exit(1);
    }
    
    if(pid2 == 0){
        //Child process 2(wc)
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execvp("wc", argv);
    }
    
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return 0;
}
