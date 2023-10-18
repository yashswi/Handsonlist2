/*
============================================================================
Name : 20a.c
Author :  yashswi chaturvedi
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 1st oct, 2023.
============================================================================
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include<sys/stat.h>

//write end of the one way communication

int main()
{
    char data[] = "Sending data in one way comm. manner";
    int fd,w;
    char fifo[] = "./myfifo";

    mkfifo(fifo, S_IRWXU);

    if (mkfifo(fifo, S_IRWXU) == -1)
        printf("\nError while creating FIFO file!");
    if((fd = open(fifo, O_WRONLY)) == -1)
	printf("\nError while opening FIFO file!");
    else
    {
        if(write(fd, &data, sizeof(data))==-1)
            printf("\nError while writing to the FIFO file!");
        close(fd);
    }
    return 0;
}
