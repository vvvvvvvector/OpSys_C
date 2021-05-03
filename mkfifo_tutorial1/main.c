#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(mkfifo("myfifo1", 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create fifo file\n");
            _exit(1);
        }
    }

    printf("opening...\n");
    int fd = open("myfifo1", O_WRONLY);
    if(fd == -1){
        perror("open file error\n");
        _exit(1);
    }
    printf("opened.\n");
    char message[31] = "Hello World\n";
    if(write(fd, message, strlen(message) + 1) == -1){
        perror("writing error\n");
        _exit(1);
    }
    printf("written\n");
    close(fd);
    printf("closed\n");
    
    return 0;
}