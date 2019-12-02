#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
    printf("Demonstration of kill\n\n");
    int status;
    pid_t pid; 
    if ((pid = fork()) == 0) 
        while(1){
            printf("yaay\n");
        }
    else
    { 
        kill(pid, SIGINT); 
        wait(&status); 
        if (WIFSIGNALED(status)) 
            psignal(WTERMSIG(status), "Child terminated due to"); 
    } 
} 