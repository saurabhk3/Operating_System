//Client - writes
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include<stdlib.h>

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
	message.mesg_type = 1; 

	printf("Write Data : ");
   	scanf("%s",message.mesg_text);
	if((msgsnd(msgid, &message, sizeof(message), 0))<0){
        perror("Error in writing\n");
        exit(1);
    }
	printf("Data send is : %s \n", message.mesg_text); 

	return 0; 
} 
