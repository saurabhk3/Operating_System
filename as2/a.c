#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
void handle_sigint(int sig){
	pid_t p;
	p = fork();
	printf("Parent\t: %d,%d\n",getpid(),getppid());
	if(p==0){
		
		printf("\nPID is %d and PPID is %d\n",getpid(),getppid());
		exit(1);
	}
	exit(1);
}
int main(){
	signal(SIGINT, handle_sigint);	
	printf("\npid %d ppid %d",getpid(),getppid());
	printf("Waiting for the interrupt\n");
	while(1){
		;
	}
	return 0;
}

