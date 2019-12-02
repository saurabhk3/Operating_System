//Server - reads 
#include <stdio.h> 
#include <sys/ipc.h> 
#include<stdlib.h>
#include <sys/msg.h> 
struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	key_t key; 
	int msgid; 

	
	key = ftok("/Documents/OS/as4", 65); 
	msgid = msgget(key, 0666 | IPC_CREAT);  
	if((msgrcv(msgid, &message, sizeof(message), 1, 0))<0){
        perror("Error\n");
        exit(1);
    }

	printf("Data Received is : %s \n",message.mesg_text); 
	msgctl(msgid, IPC_RMID, NULL); // destroys the msg queue

	return 0; 
} 
