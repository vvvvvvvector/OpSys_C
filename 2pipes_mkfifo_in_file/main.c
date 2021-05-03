#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

// find /etc/ | head -3 | wc -c
int main(){
    if(mkfifo("myfifo1", 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create fifo file\n");
            _exit(1);
        }
    }

    if(mkfifo("myfifo2", 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create fifo file\n");
            _exit(1);
        }
    }

    int pid;

    if((pid = fork()) == 0){
        int desk = open("myfifo1", O_WRONLY);
        dup2(desk, 1);
        close(desk);
        execlp("find", "find", "/etc/", NULL);
        perror("blad uruchomenia programu 1");
        _exit(1);
    }

    if((pid = fork()) == 0){
        int desk1 = open("myfifo1", O_RDONLY);
        int desk2 = open("myfifo2", O_WRONLY);
        dup2(desk1, 0);
        dup2(desk2, 1);
        close(desk1);
        close(desk2);
        execlp("head", "head", "-3", NULL);
        perror("blad uruchomenia programu 2");
        _exit(1);
    }

    if((pid = fork()) == 0){
        int desk = open("myfifo2", O_RDONLY);
        int file = open("plik.txt", O_WRONLY | O_CREAT, 0777);
        dup2(desk, 0);
        dup2(file, 1);
        close(desk);
        close(file);
        execlp("wc", "wc", "-c", NULL);
        perror("blad uruchomenia programu 2");
        _exit(1);
    }
    
    return 0;
}