/*
============================================================================
Name : 25.c
Author :  yashswi chaturvedi
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
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
    struct msqid_ds mds; //Message Queue information

    key = ftok(".", 'a'); //ascii value i.e., 97
    if (key == -1)
        printf("\nError while computing key!");
    else
    {
    	msgqid = msgget(key, IPC_CREAT | 0744);
    	if(msgqid == -1)
        	printf("\nError while creating Message Queue!");
	else
	{
    		printf("Key: %d\n", key);
    		printf("Message Queue Identifier: %d\n\n", msgqid);

    		if(msgctl(msgqid, IPC_STAT, &mds) == -1)
        		printf("\nError while getting Message Queue info!");
		else
		{
    			printf("Access Permission: %od\n", mds.msg_perm.mode);
    			printf("UID: %d\n", mds.msg_perm.uid);
    			printf("GID: %d\n", mds.msg_perm.gid);
    			printf("Time of last message sent: %ld\n", mds.msg_stime);
    			printf("Time of last message received: %ld\n", mds.msg_rtime);
    			printf("Size: %ld\n", mds.__msg_cbytes);
    			printf("Number of messages: %ld\n", mds.msg_qnum);
    			printf("Maximum number of bytes allowed: %ld\n", mds.msg_qbytes);
    			printf("PID of last sent message: %d\n", mds.msg_lspid);
    			printf("PID of last received message: %d\n", mds.msg_lrpid);
		}
	}
    }
    return 0;
}

