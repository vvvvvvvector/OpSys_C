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
    srand(time(NULL));
    int size = 5;
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    int fd = open("sum", O_WRONLY);
    if(fd == -1){
        perror("opening error\n");
        _exit(1);
    }

    if(write(fd, arr, sizeof(int) * size) == -1){
        perror("writing error\n");
        _exit(1);
    }
    close(fd);

    fd = open("sum", O_RDONLY);
    int sum;
    read(fd, &sum, sizeof(int));
    close(fd);
    printf("received sum = %d\n", sum);

    return 0;
}