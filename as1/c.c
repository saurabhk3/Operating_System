#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<utmp.h>

int main(int argc,char* argv[]){
	int pid;
	pid = fork();
	if(pid==0){
		execv(argv[1],argv);
		printf("Child done\n");
		exit(0);
	}
	int stat;
	int child = wait(&stat);
	if(WIFEXITED(stat)){
		printf("Child pid:%d,exit code:%d\n",(int)child,WEXITSTATUS(stat));
		printf("Wait over\n");
		//printf("No of process exited:%d\n,"WTERMSIG(stat));
	}
        return 0;
}

