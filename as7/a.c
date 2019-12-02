#include <sys/types.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <fcntl.h>
#include <limits.h>
#include<signal.h>

#define PERMS 0666
struct sembuf p = {0,-1,SEM_UNDO};
struct sembuf v = {0,1,SEM_UNDO};
union semun{
    int val;
    struct semid_ds * buf;
    unsigned short * array;
    }arg;
int semid;
void sigintHandler(){
    printf("Killing semaphore");
    semctl(semid,IPC_RMID,0);
    exit(0);
}
int main(){

    signal(SIGINT,sigintHandler);
    FILE * fptr;
    key_t key;
    char * rd;
    
    int semflg = 0666 | IPC_CREAT;
    int nsems = 1;
    char * path = "/Documents/OS/as7";
     key = ftok(path,65);

    if((semid = (semget(key,nsems,semflg)))==-1){
        perror("semget failed");
        exit(1);
    }else{
         arg.val = 1;
        if(semctl(semid,0,SETVAL,arg)<0)
        {
            printf("couldnt set\n");
            exit(1);
        }
        while(1){
            printf("Waiting...\n");
            //wait(1);
           
            //entry sec
            if((semop(semid,&p,1))<0){
                perror("semop ");
                exit(1);
            }
            //critical sec.
            if((fptr = fopen("/Documents/OS/as7/test.txt","r"))<0){
                perror("file ");
            }
            fscanf(fptr,"%s",rd);
            printf("%s",rd);
            rewind(fptr);
            printf("\nSleeping for 5 secs\n");
            sleep(2);
            // exit section
            semop(semid,&v,1);
            printf("Exiting..");
            
        }
        
        
    }





    return 0;
}