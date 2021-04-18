#include <stdio.h>

int main(int argc, char *argv[]){
    close(1);
    creat("plik.txt", 0777);
    execvp("ls", argv);
    return 0;
}
