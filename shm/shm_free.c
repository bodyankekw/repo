#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int *array;
    int shmid;
    char pathname[] = "sys1.c";
    key_t key;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
        printf("Can't get shared memory\n");
        exit(-1);
    }

    if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Can't remove shared memory\n");
        exit(-1);
    }

    return 0;
}