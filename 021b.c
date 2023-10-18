
/*
============================================================================
Name : 21b.c
Author :  yashswi chaturvedi
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 1st oct, 2023.
============================================================================
*/


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//2 way communication - this will first receive data from 21a and print it
//then send data to 21a

int main()
{
    char send[] = "Sending data from 21b to 21a";
    char receive[50];

    int fd1; //for sending
    int fd2;  //for receiving
    char fifo1[] = "./myfifo1";
    char fifo2[] = "./myfifo2";

        //create myfifo1 for sending the data to b
    mkfifo(fifo2, S_IRWXU);
        //printf("\nError while creating FIFO file in 21b !");

        //first read
    if((fd2 = open(fifo1, O_RDONLY, 0744)) == -1)
        printf("\nError while opening the receiving fifo file in 21a!");
    else{
        if(read(fd2, &receive, sizeof(receive)) == -1)
                printf("\nError reading the received file in 21a");
        close(fd2);
    }

    printf("Received: %s - from 21a", receive);

	//then write
    if((fd1 = open(fifo2, O_WRONLY, 0744)) == -1)
        printf("\nError while opening the sending fifo file in 21b!");
    else
    {
        if(write(fd1, &send, sizeof(send))==-1)
            printf("\nError while writing to the FIFO file in 21b!");
        close(fd1);
    }

    return 0;
}
