/*
 * ============================================================================
 Name : 30.c
 Author : yashswi chaturvedi
 Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
 Date: 10th OCT, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shm_id;
    key_t key = ftok("shared_memory_example", 65); // Generate a key for the shared memory

    // Create shared memory segment
    shm_id = shmget(key, 1024, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory segment
    char *data = (char *)shmat(shm_id, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Write data to shared memory
    strcpy(data, "Hello, shared memory!");

    printf("Data written to shared memory: %s\n", data);

    // Detach shared memory segment with read-only permissions
    shmdt(data);

    // Try to overwrite the data (this will fail because it's read-only)
    data = (char *)shmat(shm_id, NULL, SHM_RDONLY);
    if (data == (char *)(-1)) {
        perror("shmat failed (read-only)");
    } else {
        strcpy(data, "This will not work!");
        printf("Attempted to overwrite: %s\n", data);
        shmdt(data);
    }

    // Detach shared memory segment
    shmdt(data);

    // Remove shared memory segment
    shmctl(shm_id, IPC_RMID, NULL);

    printf("Shared memory removed\n");

    return 0;
}

