#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/signal.h>

void handler(int sig){
    int pipefd[2],buf;
    pid_t cpid;
    
    if(pipe(pipefd)==-1){
        perror("pipe");
        exit(1);
    }
    cpid = fork();
    if(cpid==-1){
        perror("fork");
        exit(1);
    }
    if(cpid == 0){
        int n,i;
        printf("Child: enter value of n:");
        scanf("%d",&n);
        close(pipefd[0]);
        if(n<0){
            printf("Enter positive value of N\n");
        }
        int a=1,b=1;
        buf = getpid();
        write(pipefd[1],&buf,sizeof(buf));   //sending PID of child process 
        for(i=0;i<n;i++){ 
            if(i<2){
                write(pipefd[1],&a,sizeof(a));
            }else{  
                buf = a+b;
                a = b;
                b = buf;
                write(pipefd[1],&buf,sizeof(buf));
                }
        }
        close(pipefd[1]);
    
        exit(0);
    }
    printf("Parent\n");
    close(pipefd[1]);
    bzero(&buf,sizeof(buf));
    read(pipefd[0],&buf,sizeof(buf));
    printf("PID : %d\n",buf);
   
   while(read(pipefd[0],&buf,sizeof(buf))>0){
      // write(STDOUT_FILENO,&buf,sizeof(buf));
       printf("\t%d ",buf);
       }
    printf("\n");
    close(pipefd[0]);
    wait(NULL);
    exit(0);
}
int main(){
    signal(SIGINT,handler);
    printf("CTRL + C for interrupt\n");
    while(1);
  //  sleep(1);
    return 0;
}
