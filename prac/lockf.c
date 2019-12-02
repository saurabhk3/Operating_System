#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char**argv){
    int fd;
    char path[90] ;
    //fd = open(path,0666);
    //lockf
    printf("[Hello]\n");
    write(1,"fd for stdout is 1",19);
    read(2,path,sizeof(path));
    printf("%s",path);
    
    return 0;
}