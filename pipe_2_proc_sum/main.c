#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int fd_1[2];
    int fd_2[2];
    int arr[] = {3,20,1,2,5,8,9,11,5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int start, end;
    if(pipe(fd_1) == -1){
        return 1;
    }
    if(pipe(fd_2) == -1){
        return 2;
    }
    if(fork() == 0){
        start = 0;
        end = arr_size / 2;
        int sum1 = 0;
        for(int i = start; i < end; i++){
            sum1 += arr[i];
        }
        printf("sum1 = %d\n", sum1);
        close(fd_1[0]);
        write(fd_1[1], &sum1, sizeof(int));
        close(fd_1[1]);
    } else {
        if(fork() == 0){
            start = arr_size / 2;
            end = arr_size;
            int sum2 = 0;
            for(int i = start; i < end; i++){
                sum2 += arr[i];
            }
            printf("sum2 = %d\n", sum2);
            close(fd_2[0]);
            write(fd_2[1], &sum2, sizeof(int));
            close(fd_2[1]);
        } else{
            wait(NULL);
            close(fd_1[1]);
            close(fd_2[1]);
            int sum1;
            read(fd_1[0], &sum1, sizeof(int));
            int sum2;
            read(fd_2[0], &sum2, sizeof(int));
            close(fd_1[0]);
            close(fd_2[0]);
            int totalSum = sum1 + sum2;
            printf("total sum = %d\n", totalSum);
        }
    }
    return 0;
}
