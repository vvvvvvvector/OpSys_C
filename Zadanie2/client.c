#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#define MAX 2

int main(int argc, char *argv[]){
    char message[101] = {0};
    int lbajt;

    if(mkfifo(argv[1], 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create client fifo\n");
            _exit(1);
        }
    }

    int client_to_server = open("server_fifo", O_WRONLY);
    if(client_to_server == -1){
        perror("blad otwarcia client_to_server\n");
        _exit(1);
    }

    int server_to_client = open(argv[1], O_RDONLY);
    if(server_to_client == -1){
        perror("blad otwarcia server_to_client\n");
        _exit(1);
    }

    write(client_to_server, argv[1], sizeof(argv[1]));

    while((lbajt = read(server_to_client, message, 1) > 0)){
        printf("%s", message);
    }

    if(close(client_to_server) == -1 || close(server_to_client) == -1){
        perror("blad zamkniecia plikow\n");
        _exit(1);
    }

    unlink(argv[1]);
    
    return 0;
}