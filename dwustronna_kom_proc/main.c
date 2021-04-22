#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

//Dwustronna komunikacja między procesami
int main(){
    int fd_1[2], fd_2[2];
    char pipe1writemessage[20] = "Hi";
    char pipe2writemessage[20] = "Hello";
    char readmessage[20];
    
    if(pipe(fd_1) == -1){
        perror("Unable to create pipe 1");
        exit(1);
    }
    
    if(pipe(fd_2) == -1){
        perror("Unable to create pipe 2");
        exit(1);
    }
    
    if(fork() == 0){
        close(fd_1[0]);
        close(fd_2[1]);
        printf("Child: Writing to pipe 1 – Message is %s\n", pipe1writemessage);
        write(fd_1[1], pipe1writemessage, sizeof(pipe1writemessage));
        read(fd_2[0], readmessage, sizeof(readmessage));
        printf("Child: Reading from pipe 2 – Message is %s\n", readmessage);
    } else {
        close(fd_1[1]);
        close(fd_2[0]);
        read(fd_1[0], readmessage, sizeof(readmessage));
        printf("Parent: Reading from pipe 1 – Message is %s\n", readmessage);
        printf("Parent: Writing to pipe 2 – Message is %s\n", pipe2writemessage);
        write(fd_2[1], pipe2writemessage, sizeof(pipe2writemessage));
    }
    
    return 0;
}
