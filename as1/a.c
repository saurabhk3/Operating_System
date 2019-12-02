#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	char s[100],v;
	int pid,ppid,j=1,count=0;
	FILE * fp,*counter;
	fp = fopen("pid1.txt","w");
	counter = fopen("count1.txt","w");
	pid_t pidch=fork();
	if(pidch==0)
	{
		pid = getpid();
		ppid = getppid();
		j = 1;  //first child process
		v ='a';
		//fprintf(counter,"%c\n",v);
		fprintf(fp,"PID 1 = %d , PPID1 = %d\n",pid,ppid);
		fprintf(counter,"%d\n",j);
		fclose(fp);
		fclose(counter);
		if(fork()==0)
		{
			pid = getpid();
			ppid = getppid();
			j = 1;
			v = 'b';
			fp = fopen("pid1.txt","a");
			counter = fopen("count1.txt","a");
			fprintf(counter,"%d\n",j);
			fprintf(fp,"PID2 = %d , PPID2 = %d\n",pid,ppid);
			printf("\nCSB17055\n");
			fclose(fp);
			fclose(counter);
			exit(0);
		} 
		wait(NULL);
//		printf("Child exits");
		exit(0);
	}
	wait(NULL);
//	printf("parent wait over");
	v = 'c';
	fp = fopen("pid1.txt","a");
        counter = fopen("count1.txt","a");
	fprintf(counter,"%d\n",j);
	fp = fopen("pid1.txt","r");
        counter = fopen("count1.txt","r");
	rewind(counter);
	count=0;
//	while((fscanf(counter,"%d",&j)==1)){
	while(!feof(counter)){
		fscanf(counter,"%d",&j);
		printf("%d ",j);
		count++;
	}
	printf("Total number of process: %d\n",count);
	rewind(fp);

	while((fscanf(fp,"%s",s)==1)){
		printf("%s",s);
	}
	fclose(fp);
	return 0;
}

