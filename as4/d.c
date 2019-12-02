#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main()
{
char fname[]="test.txt";
struct flock f;
int fd;
 
fd = open( fname, O_RDWR );
if( fd == -1 ) {
printf("Failed to open %s",fname);  /* error handling */
}
 
f.l_type = F_WRLCK;
f.l_start = 0;
f.l_whence = SEEK_SET;
f.l_len = 0;
 
if( fcntl( fd, F_SETLK, &f ) < 0 ) {
  perror( "Failed to lock" );
}
 
getchar(); /* to keep the file locked*/
return 0;
}