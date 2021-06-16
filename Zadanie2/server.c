#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#define MAX 20

int main(){
    char nazwa_kol[20] = {0};
    int lbajt;
    
    if(mkfifo("server_fifo", 0777) == -1){
        if(errno != EEXIST){
            perror("couldnt create fifo file\n");
            _exit(1);
        }
    }

    printf("server is waiting on fifo: server_fifo\n");

    int client_to_server = open("server_fifo", O_RDONLY);

    //do {
    //    read(client_to_server, nazwa_kol, MAX);
    //    int temp;
    //    if(fork() == 0){
    //        temp = open(nazwa_kol, O_WRONLY);
    //        char buf1[31];
    //        char buf2[31];
    //        sprintf(buf1, "In FIFO: %s\n", "server_fifo");
    //        sprintf(buf2, "Out FIFO: %s\n", nazwa_kol);
    //        write(temp, "Connection Accepted\n", strlen("Connection Accepted\n"));
    //        write(temp, buf1, strlen(buf1));
    //        write(temp, buf2, strlen(buf2));
    //        close(temp);
    //        _exit(0);
    //    }
    //}while (1);

    read(client_to_server, nazwa_kol, MAX);
    int server_to_client = open(nazwa_kol, O_WRONLY);
    char buf1[31];
    char buf2[31];
    sprintf(buf1, "In FIFO: %s\n", "server_fifo");
    sprintf(buf2, "Out FIFO: %s\n", nazwa_kol);
    printf("Connection accepted\n");
    write(server_to_client, "Connection Accepted\n", strlen("Connection Accepted\n"));
    write(server_to_client, buf1, strlen(buf1));
    write(server_to_client, buf2, strlen(buf2));

    close(client_to_server);
    close(server_to_client);
    unlink("server_fifo");

    return 0;
}