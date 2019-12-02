#include <sys/times.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

int main(){
    struct tms before,after;
    gettimeofday(&before,NULL);
    if(fork()==0){
        int i=0;
        while(i<100000){
            i++;
            
        }
        sleep(5);
        exit(0);
    }
    printf("Child : u_time : %f   s_time : %f\n",(double)before.tms_cutime,(double)before.tms_cstime);

    gettimeofday(&after,NULL);
    
    wait(NULL);
    printf("Parent : utime : %f   s_time : %f\n",(double)after.tms_utime,(double)after.tms_stime);
   
    return 0;
}