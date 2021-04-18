#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

//fd[0] - reading, fd[1] - writing
int main() {
    int fd[2], nbytes;
    pid_t childpid;
    //char str[] = "Hello world!\n";
    char str_tab[2][20] = {"hello\n", "world\n"};
    char readBuf[2][81];
    
    pipe(fd);
    
    if((childpid = fork()) == -1){
        perror("fork...");
        exit(1);
    } 
    
    if(childpid == 0){
        close(fd[0]); 
        int len = strlen(str_tab[0]) + 1;
        printf("zapisuje: %s", str_tab[0]);
        write(fd[1], &len, sizeof(int));
        write(fd[1], str_tab[0], len);
        int len1 = strlen(str_tab[1]) + 1;
        printf("zapisuje: %s", str_tab[1]);
        write(fd[1], &len1, sizeof(int));
        write(fd[1], str_tab[1], len1);
        close(fd[1]);
    } else {
        close(fd[1]);
        int str_len;
        nbytes = read(fd[0], &str_len, sizeof(int));
        nbytes += read(fd[0], readBuf[0], str_len);
        printf("czytam string 0: %s", readBuf[0]);
        int str_len1;
        nbytes += read(fd[0], &str_len1, sizeof(int));
        nbytes += read(fd[0], readBuf[1], str_len1);
        printf("czytam string 1: %s", readBuf[1]);
        close(fd[0]);
    }
    
    return 0;
}
