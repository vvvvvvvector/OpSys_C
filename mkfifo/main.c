#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 512

int main(int argc, char *argv[]){
    int pdesk;
    
    if(mkfifo("kolejka", 0600) == -1){
        perror("Tworzenie kolejki FIFO");
        exit(1);
    }
    
    if(fork() == 0){
        close(1);
        open("kolejka", O_WRONLY);
        execvp("ls", argv);
        perror("Uruchomenie programu");
        exit(1);
    } else {
        char buf[MAX];
        int lbajt;
        pdesk = open("kolejka", O_RDONLY);
        while((lbajt = read(pdesk, buf, MAX)) > 0){
            write(1, buf, lbajt);
        }
    }
    
    return 0;
}
