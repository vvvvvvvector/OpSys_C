#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

//ps -laef | cut -c 48- | sort | uniq -c | sort -n
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

    if(mkfifo("myfifo3", 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create fifo file\n");
            _exit(1);
        }
    }

    if(mkfifo("myfifo4", 0777) == -1){
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
        execlp("ps", "ps", "-laef", NULL);
        perror("blad uruchomienia programu 1");
        _exit(1);
    }

    if((pid = fork()) == 0){
        int desk1 = open("myfifo1", O_RDONLY);
        int desk2 = open("myfifo2", O_WRONLY);
        dup2(desk1, 0);
        dup2(desk2, 1);
        close(desk1);
        close(desk2);
        execlp("cut", "cut", "-c", "48-", NULL);
        perror("blad uruchomienia programu 2");
        _exit(1);
    }

    if((pid = fork()) == 0){
        int desk1 = open("myfifo2", O_RDONLY);
        int desk2 = open("myfifo3", O_WRONLY);
        dup2(desk1, 0);
        dup2(desk2, 1);
        close(desk1);
        close(desk2);
        execlp("sort", "sort", NULL);
        perror("blad uruchomienia programu 3");
        _exit(1);
    }

    if((pid = fork()) == 0){
        int desk1 = open("myfifo3", O_RDONLY);
        int desk2 = open("myfifo4", O_WRONLY);
        dup2(desk1, 0);
        dup2(desk2, 1);
        close(desk1);
        close(desk2);
        execlp("uniq", "uniq", "-c", NULL);
        perror("blad uruchomienia programu 4");
        _exit(1);
    }

    if((pid = fork()) == 0){
        int desk = open("myfifo4", O_RDONLY);
        int file = open("file.txt", O_WRONLY | O_CREAT, 0777);
        dup2(desk, 0);
        dup2(file, 1);
        close(desk);
        close(file);
        execlp("sort", "sort", "-n", NULL);
        perror("blad uruchomienia programu 5");
        _exit(1);
    }
    
    return 0;
}