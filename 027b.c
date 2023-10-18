/*
============================================================================
Name : 27b.c
Author :  yashswi chaturvedi
Description : Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 1st oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    key_t key;
    int msgqid;
    ssize_t m;

    struct message
    {
        long int msg_type;     // Used to identify message type - should be > 0
        char msg_text[50]; // msg
    } msg;

    if((key = ftok(".", 'a')) == -1)
        printf("\nError while creating key!");

    if((msgqid = msgget(key, IPC_CREAT | 0744))==-1)
        printf("\nError while creating message queue!!!");

    msg.msg_type = 1; //imp tp receive msg as msg type will be checked
    printf("\n Key:%d and msqid:%d\n", key, msgqid);

    m = msgrcv(msgqid, (void *)&msg, sizeof(msg), msg.msg_type, IPC_NOWAIT);

    if (m == -1)
        printf("\nError while receiving!");
    else
        printf("\nReceived the text: %s", msg.msg_text);

  return 0;
}

