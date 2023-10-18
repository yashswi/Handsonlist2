/*
============================================================================
Name : 22b.c
Author :  yashswi chaturvedi
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 1st oct, 2023.
============================================================================
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>//for select system call

int main()
{
	//for fifo
    int fd;
    char data[100];

	//for select
    fd_set readfds;
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec=0;
    int retval;

    if((fd = open("myfifo", O_RDONLY))==-1)
	printf("\n Error opening fifo file!");

    printf("\nWaiting for someone to write into fifo...\n");

    //add fifo file's fd to the fd_set which is watched over by select
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    retval=select(fd+1, &readfds, NULL, NULL, &timeout);

    if(retval==-1)
        printf("\nError!!");
    else if(retval)
	{
		printf("\nData is availabel now...");
		//printing the data
		if((read(fd, &data, sizeof(data)))==-1)
		    printf("\n Error while reading from the FIFO file!!!");
		else
		    printf("\nThe availabel data is %s", data);
	}
    else
        printf("\nSorry, No data within 10 seconds!!!");

    close(fd);

  return 0;
}
