#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>

#define PERMS 0666
int main(){
    int shmid;
    int *ptr;
    int pid = getpid();
    
    key_t key = ftok("/Documents/OS/as6",65);
   
    shmid = shmget(key,sizeof(int),PERMS | IPC_CREAT);

    ptr =(int*) shmat(shmid,(void*)0,0);  // shmaddr = 0 means system select the address for caller
    
    printf("Sending process id :%d",pid);
    
    ptr[0] = getpid();
    printf("\nData sent\n");

    shmdt((void*)ptr);

   
    return 0;
    
}