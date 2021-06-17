#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, 1024, 0777 | IPC_CREAT);
    if (shmid == -1) {
        perror("failed to create shared memory segment\n");
        _exit(1);
    }

    char *str = (char*) shmat(shmid, NULL, 0);
    if (str == NULL) {
        perror("failed to attach shared memory segment\n");
        _exit(1);
    }

    printf("write data: ");
    fgets(str, 1024, stdin);

    printf("data written in memory: %s", str);

    shmdt(str);
    
    return 0;
}