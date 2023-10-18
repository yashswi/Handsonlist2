/*
============================================================================
Name : 19
Author : yashswi chaturvedi
Description : Create a FIFO file by
a. mknod system call
b. mkfifo library function
Date: 10-october-2023
============================================================================
*/
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {

    // Using mknod system call
    if (mknod("mknod_fifo", S_IFIFO | 0777, 0) == -1) {
        perror("mknod");
        return 1;
    } else {
        printf("FIFO file created using mknod\n");
    }

    // Using mkfifo library function
    if (mkfifo("mkfifo_fifo", 0777) == -1) {
        perror("mkfifo");
        return 1;
    } else {
        printf("FIFO file created using mkfifo\n");
    }

    return 0;
}

