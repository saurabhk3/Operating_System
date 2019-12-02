#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char* argv[])
{
 char* file = "as4.txt";
 int fd;
 struct flock lock;

 printf ("opening %s\n", file);
 
 fd = open (file, O_WRONLY);
 printf ("locking\n");
 
 memset (&lock, 0, sizeof(lock));
 lock.l_type = F_WRLCK;
    while(1){
        fcntl (fd, F_SETLKW, &lock);
    
        printf ("locked\nhit Enter to unlock... ");
  //      getchar ();
        sleep(3);
        printf ("UNLOCKING..\n");
        lock.l_type = F_UNLCK;
        fcntl (fd, F_SETLKW, &lock);
    }

 close (fd);
 return 0;
}