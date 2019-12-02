#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>

int main (int argc, char* argv[])
{
 char* file = "text.txt";
 int fd;
 char buf[1000];
 struct flock lock,slock;

 printf ("opening %s\n", file);
 fd = open ("text.txt", O_RDONLY);
 printf ("Locking...\n");
 memset (&lock, 0, sizeof(lock));
 lock.l_type = F_WRLCK;
 lock.l_start = 0;
 lock.l_whence = SEEK_SET;
 lock.l_len = 100;
 lock.l_pid = 0;
 slock = lock;

read(fd,&buf,sizeof(buf));
printf("%s \n",buf);
 
 printf("Setting lock\n");
 fcntl(fd,F_GETLK,&lock);
 if(lock.l_type==F_WRLCK){
     printf("locked!\n");
 }else{
     printf("lock error\n");
 }
 return 0;
}