// to show that ipc identifiers range upto 65,535 - systemwide unique
//(file descriptors range for a short value as they are process specific)
#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define PERMS 0666
#define KEY ((key_t)98765L)
int main(){
    int msqid;
    for(int i=0;i<15;i++){
        if((msqid = msgget(KEY,PERMS |IPC_CREAT))<0){
            perror("Can't create msgqueue\n");
        }
        printf("Msgqid : %d\n",msqid);

        if(msgctl(msqid,IPC_RMID,(struct msqid_ds *)0)<0){
            perror("Error in removing\n");
        }
    }

}