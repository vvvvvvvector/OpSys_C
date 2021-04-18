#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX 1024

int main(int argc, char *argv[]) {
    char buf[MAX];
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("blad otwarcia pliku do odczytu");
        exit(1);
    }
    int lbajt = read(fd, buf, MAX);
    close(fd);
    fd = open(argv[1], O_WRONLY);
    if(fd == -1){
        perror("blad otwarcia pliku do zapisu");
    }
    for(int i = 0;;){
        int len = i;
        while(buf[len] != '\n') len++;
        if(buf[len + 1] == '\0') break;
        if(i == 0){
            for(int j = 0; j < len / 2; j++){
                char temp = buf[i + j];
                buf[i + j] = buf[len - 1 - j];
                buf[len - 1 - j] = temp;
            }
        }
        else{
            for(int j = 0; j < (len - i + 1) / 2; j++){
                char temp = buf[i - 1 + j];
                buf[i - 1 + j] = buf[len - 1 - j];
                buf[len - 1 - j] = temp;
            }
        }
        i = len + 2;
    }
    if(write(fd, buf, lbajt) == -1){
        perror("blad zapisu pliku");
        exit(1);
    }
    close(fd);
    return 0;
}
