#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    int fd;
    char *myfifo = "/tmp/myfifo";
    char arr1[80], arr2[80];

    if(mkfifo(myfifo, 0666) == -1){
        perror("Tworzenie kolejki FIFO");
		exit(1);
    }
    
    while(1){
        fd = open(myfifo, O_WRONLY);
        fgets(arr2, 80, stdin);
        write(fd, arr2, strlen(arr2) + 1);
        close(fd);

        fd = open(myfifo, O_RDONLY);
        read(fd, arr1, sizeof(arr1));
        printf("user 2: %s\n", arr1);
        close(fd);
    }
    
    return 0;
}