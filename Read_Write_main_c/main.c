#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX 2

int main(int argc, char *argv[]){
    int desc_zrod, desc_cel = 1;
    int lbajt;
    char buf[MAX];
    
    desc_zrod = open(argv[1], O_RDONLY);
    if(desc_zrod == -1){
        perror("Blad otwarcia pliku zrodlowego");
		exit(1);
    }
    
    while((lbajt = read(desc_zrod, buf, MAX)) > 0){
        if(write(desc_cel, buf, lbajt) == -1){
            perror("Blad zapisu");
            exit(1);
        }
    }
    
    if(lbajt == -1){
        perror("Blad odczytu pliku zrodlowego");
        exit(1);
    }
    
    if(close(desc_zrod) == -1 || close(desc_cel) == -1){
        perror("blad zamkiencia pliku");
        exit(1);
    }
    
    return 0;
}
