#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){

    int desc_zrod = open(argv[1], O_RDONLY);
    if(desc_zrod == -1){
        perror("blad otwarcia pliku");
        _exit(1);
    }
    int desc_cel = open(argv[2], O_WRONLY | O_CREAT, 0777);
    if(desc_cel == -1){
        perror("blad otwarcia pliku");
        _exit(1);
    }

    long size = lseek(desc_zrod, 0, SEEK_END);
    if(size == -1){
        perror("blad lseek");
        _exit(1);
    }

    printf("Rozmiar pliku %s = %ld\n", argv[1], size);
    char buf[50] = {'\0'};
    sprintf(buf, "%ld \n", size);
    
    if(write(desc_cel, buf, strlen(buf) + 1) == -1){
        perror("blad odczytu");
        _exit(1);
    }

    if(close(desc_zrod) == -1 || close(desc_cel) == -1){
        perror("blad zamkniecia");
        _exit(1);
    }
    
    return 0;
}