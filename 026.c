/*
============================================================================
Name :26.c
Author : yashswi chaturvedi
Description : Write a program to send messages to the message queue. Check $ipcs -q.
Date: 1st oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    key_t key;
    int msgqid;
    int status;

    struct msgContent
    {
        long msgtype; //id
        int n; //message
    } message;

    if((key = ftok(".", 'a')) == -1)
        printf("\nError while computing key!");

    if ((msgqid=msgget(key, IPC_CREAT | 0700)) == -1)
        printf("\nError while creating message queue!");

    message.msgtype = 82;
    message.n = 8299;

    status = msgsnd(msgqid, &message, sizeof(message), 0);

    if (status == -1)
        printf("\nError while sending message!");
    else
    	printf("\nMessage sent successfully!\n use 'ipcs -q'");

    return 0;
}

