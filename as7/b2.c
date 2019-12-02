#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/sem.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>

#define PERMS 0666

int semid;

void sigHandler(int sig){
    printf("killing semaphore\n");
    if((semctl(semid,0,IPC_RMID,0))>=0){
        printf("Killed\n");
        exit(1);
    }
}
struct sembuf v = {0,-1,SEM_UNDO};  //wait  sem_num,sem_op,sem_flg
struct sembuf p = {0,1,SEM_UNDO};  //signal
struct semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}arg;
int c=0;
int main(){
  //  signal(SIGINT,sigHandler);
    key_t key = ftok("/Document/OS/as7",'b'); //'a' = 65
    FILE *fp;
    char buf[100];
    
    if((semid = semget(key,1,IPC_CREAT | PERMS))<0){
        perror("semget()\n");
        exit(1);
    }else{
        printf("successfully created %d\n",semid);
    }
    // arg.val = 1;  //initially locked
    // if(semctl(semid,0,SETVAL,arg)<0){
    //     perror("semctl\n");
    //     exit(1);
    // }s
    int count=0;
    
    signal(SIGINT,sigHandler);
    while(1){
        count++;
        printf("Waiting\n");
        if((semop(semid,&p,1))<0){
            perror(" 00 semop error");
            exit(1);
        }
            
        if((fp=fopen("test.txt","r"))<0){
            perror("file\n");
            exit(1);
        }rewind(fp);
        while(!feof(fp)){
            fscanf(fp,"%s",buf);
            printf("%s\n",buf);
        }
        // rewind(fp);
        fclose(fp);
        printf("\nsleeping for 3 secs %d\n",c);
        sleep(3);
        printf("Waking up\n");
        if((semop(semid,&v,1))<0){
            perror("01 semop error");
            exit(1);
        }
    
        
    }
    if((semctl(semid,0,IPC_RMID,0))<0){
        perror("RMID");
    }
    return 0;
}