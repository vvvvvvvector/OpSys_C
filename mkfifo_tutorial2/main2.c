#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
    int arr[5];
    int size = 5;

    int fd = open("sum", O_RDONLY);
    if(fd == -1){
        perror("opening file error\n");
        _exit(1);
    }

    if(read(fd, arr, sizeof(int) * size) == -1){
        perror("reading error\n");
        _exit(1);
    }
    close(fd);  
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    printf("sum result is %d\n", sum);

    fd = open("sum", O_WRONLY);
    write(fd, &sum, sizeof(int));
    close(fd);
    
    return 0;
}