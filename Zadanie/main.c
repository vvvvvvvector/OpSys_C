#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(){  
    printf("Poczatek\n");
    printf("proces mat - pid: %d\n", getpid());
    switch (fork()){  
        case -1:
            perror("Blad utworzenia procesu potomnego");
            break;
        case 0: /* proces potomny */
            printf("1 proces potomny - pid: %d\n", getpid());
            switch (fork()){  
                case -1:
                    perror("Blad utworzenia procesu potomnego");
                    break;
                case 0: /* proces potomny */
                    printf("2 proces potomny - pid: %d, mat - pid: %d\n", getpid(), getppid());
                    printf("current pid: %d, 1 proces mat - pid: %d\n", getpid(), getppid());
                    exit(1);
                default: /* proces macierzysty */
                    if (wait(NULL) == -1)
                        perror("Blad w oczekiwaniu na zakonczenie potomka");
                    exit(1);
            }  
                default: /* proces macierzysty */
                    if (wait(NULL) == -1)
                        perror("Blad w oczekiwaniu na zakonczenie potomka");
    }  
    printf("Koniec\n");
}
