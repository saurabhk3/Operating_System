// #include <stdio.h>      
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include<stdlib.h>
// int main(int argc,char ** argv){

//   struct flock lock, savelock;
//   int fd;
   
//   fd = open("as4.txt", O_RDONLY);
//   lock.l_type = F_RDLCK;
//   lock.l_start = 0;
//   lock.l_whence = SEEK_SET;
//   lock.l_len = 50;
//   savelock = lock;
//   fcntl(fd, F_GETLK, &lock);
//   if (lock.l_type == F_WRLCK){
//       printf("File is write-locked by process %d.\n", lock.l_pid);
//       exit(1);
//   }else if(lock.l_type == F_RDLCK){
//       printf("This file is being used by some other process\n");
//       exit(0);
//   }
//   fcntl(fd, F_SETLK, &savelock);
//   //pause();
//   while(1){
//       ;
//   }
//   return 0;
// }

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>

int main (int argc, char* argv[])
{
 char* file = "as4.txt";
 int fd;
 struct flock lock,slock;
char buf[1000];
 printf ("opening %s\n", file);
 fd = open ("as4.txt", O_RDONLY);
 printf ("Locking...\n");
 memset (&lock, 0, sizeof(lock));
 lock.l_type = F_RDLCK;
 lock.l_start = 0;
 lock.l_whence = SEEK_SET;
 lock.l_len = 100;
 lock.l_pid = 0;
 slock = lock;
 fcntl(fd,F_GETLK,&lock);
 if(lock.l_type == F_RDLCK){
     printf("The file is already locked by process %d",lock.l_pid);
     exit(1);
 }
 while(1){
    fcntl (fd, F_SETLKW, &slock);
    printf ("LOCKED!\n Unlocking in 3 secs... ");
    sleep(3);
    printf ("\nUNLOCKING...\n");
    lock.l_type = F_UNLCK;
    read(fd,&buf,sizeof(buf));
    printf("Read : %s\n",buf);
    if((fcntl (fd, F_SETLKW, &lock))==1){
        printf("UNLOCKED!\n");
    }
 }
 close (fd);
 return 0;
}