/*
 * ============================================================================
 Name : 31.c
 Author : yashswi chaturvedi
 Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
 Date: 10th OCT, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {
    sem_t binarySemaphore, countingSemaphore;

    
    if (sem_init(&binarySemaphore, 0, 1) == -1) {
        perror("sem_init (binarySemaphore)");
        exit(EXIT_FAILURE);
    }

    
    if (sem_init(&countingSemaphore, 0, 3) == -1) {
        perror("sem_init (countingSemaphore)");
        exit(EXIT_FAILURE);
    }

    printf("Semaphores created and initialized successfully.\n");

    
    sem_destroy(&binarySemaphore);
    sem_destroy(&countingSemaphore);

    return 0;
}


