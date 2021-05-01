#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int pdesk[2];

    if(pipe(pdesk) == -1){
        perror("blad tworzenia potoku");
        _exit(1);
    }

    int pid = fork();
    if(pid == -1){
        perror("blad tworzenia procesu");
        _exit(1);
    }

    if(pid == 0){
        dup2(pdesk[1], 1);
        execlp("cat", "cat", "/etc/group", NULL);
        perror("blad uruchomenia programu");
        _exit(1);
    } else {
        close(pdesk[1]);

        int file = open("grupy.txt", O_WRONLY | O_CREAT, 0777);
        
        dup2(pdesk[0], 0);
        dup2(file, STDOUT_FILENO);

        execlp("head", "head", "-5", NULL);

        perror("blad uruchomenia programu");
        _exit(1);
    }
    
    return 0;
}