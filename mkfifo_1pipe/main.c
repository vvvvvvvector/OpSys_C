#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(){
    if(mkfifo("myfifo", 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create fifo file\n");
            _exit(1);
        }
    }

    if (fork() == 0) {
        int desk = open("myfifo", O_WRONLY);
        dup2(desk, 1);
        close(desk);
        execlp("ls", "ls", NULL);
        perror("blad uruchomienia programu\n");
        _exit(1);
    } else {
        int desk = open("myfifo", O_RDONLY);
        dup2(desk, 0);
        close(desk);
        execlp("tr", "tr", "a-z", "A-Z", NULL);
        perror("blad uruchomienia programu\n");
        _exit(1);
    }
    
    return 0;
}