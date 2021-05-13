#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int file = open(argv[1], O_WRONLY | O_APPEND);

    if(file == -1){
        perror("podany plik nie istnieje\n");
        _exit(1);
    }

    while(1){
        char buf[101] = {'\0'};
        fgets(buf, 101, stdin);
        if(strcmp(buf, "_end_\n") == 0){
            break;
        }
        if(write(file, buf, strlen(buf)) == -1){
            perror("blad zapisu\n");
            _exit(1);
        }
    }

    if(close(file) == -1){
        perror("blad zamkniecia\n");
        _exit(1);
    }
    return 0;
}