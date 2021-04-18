#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int pid = fork();
    
    if(pid == -1){
        perror("blad utworzenia procesu potomnego");
        exit(1);
    }
    
    if(pid == 0){
        int file = open("ping_result.txt", O_WRONLY | O_CREAT, 0777);
        
        if(file == -1){
            perror("blad otwarcia pliku");
            exit(1);
        }
        
        dup2(file, STDOUT_FILENO);
        close(file); 
        
        //execlp("ping", "ping", "-c", "3", "google.com", NULL);
        execvp("ping", argv);
    } else {
        wait(NULL);
        printf("Some post processing goes here\n");
        printf("Success!\n");
    }
    return 0;
}
