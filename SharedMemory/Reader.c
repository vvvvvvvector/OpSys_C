#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0777 | IPC_CREAT);
    if (shmid == -1) {
        perror("failed to create shared memory segment\n");
        _exit(1);
    }

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid, NULL, 0);
    if (str == NULL) {
        perror("failed to attach shared memory segment\n");
        _exit(1);
    }

    printf("data read from memory: %s", str);

    //detach from shared memory 
    shmdt(str);

     // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}