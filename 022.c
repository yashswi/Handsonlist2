/*
============================================================================
Name : 22.c
Author : yashswi chaturvedi
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 1st oct, 2023.
============================================================================
*/


#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd, w;
    char data[100]="Hello from the fifo file!";
    char path[]="myfifo";
    if((fd = open(path, O_WRONLY)) == -1)
        printf("\nError while opening FIFO file!");
    else
    {
	getchar();
        if(write(fd, data, sizeof(data))==-1)
            printf("\nError while writing to the FIFO file!");
        close(fd);
    }
    return 0;
}
