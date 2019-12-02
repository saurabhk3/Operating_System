#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<utmp.h>
#include<stdlib.h>

void print(void){
	struct utmp * log;
	setutent();
	log = getutent();
	while(log){
		printf("Logged in %s\n",log->ut_user);
		log = getutent();
	}
	endutent();
	exit(0);
}
int main(){
	printf("Start of program\n");
	if(fork()==0){
		wait(NULL);
		printf("Child created\n");
		if(fork()==0){
			print();//function
			exit(0);
		}
		exit(0);
	}else{
		wait(NULL);
		printf("Child terminated\n");
	}
	printf("Done\n");

	return 0;
}

