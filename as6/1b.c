#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

#define PERMS 0666
int main(){
    int shmid,size;
    int * ptr;
    key_t key = ftok("/Documents/OS/as6",65);
    
    shmid = shmget(key,sizeof(int),PERMS | IPC_CREAT);

    ptr = shmat(shmid,(void*)0,0);
    printf("%d ",ptr[0]);
    if(shmdt(ptr)<0){
        perror("Can't detach\n");
    }
    if((shmctl(shmid,IPC_RMID,(struct shmid_ds*) 0))<0){
        perror("Can't delete shm\n");
    }else{
        printf("\nSuccessfully removed shm\n");
    }
    return 0;
    
}