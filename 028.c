/*
============================================================================
Name : 28.c
Author :  yashswi chaturvedi
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 1st oct, 2023.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    key_t key;
    int msgqid;
    struct msqid_ds mds; //msqid data structure
    int status;

    if((key = ftok(".", 'a'))==-1)
        printf("\nError while computing key!");

    if((msgqid = msgget(key, IPC_CREAT | 0700)) == -1)
        printf("\nError while creating Message Queue!");

    printf("Key: %d\n", key);
    printf("Message Queue Identifier: %d\n\n", msgqid);

    status = msgctl(msgqid, IPC_STAT, &mds);

    if (status == -1)
        perror("/nError getting queue info!");

    printf("\n Old Permission is %o", mds.msg_perm.mode);

    printf("\nPress any key to change the permissions!\n");
    getchar();

    mds.msg_perm.mode = 0744;

    status = msgctl(msgqid, IPC_SET, &mds);

    if (status == -1)
        perror("\n cannot change queue permission!");

    printf("\n New Permission is %o", mds.msg_perm.mode);

    return 0;
}
