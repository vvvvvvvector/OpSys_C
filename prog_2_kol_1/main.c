#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int pid = fork();
    if(pid == -1){
        perror("blad tworzenia procesu");
        _exit(1);
    }

    if(pid == 0){
        printf("Zapis do pliku %s\n", argv[1]);
        int file = open(argv[1], O_WRONLY | O_CREAT, 0777);

        if(file == -1){
            perror("blad otwarcia pliku");
            _exit(1);
        }

        dup2(file, STDOUT_FILENO);
        close(file);

        execlp("ls", "ls", "-lah", NULL);
        perror("blad uruchomenia programu\n");
        _exit(1);
        
    } else {
        wait(NULL);
        printf("Koniec\n");
    }
    
    return 0;
}