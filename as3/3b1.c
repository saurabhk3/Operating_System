// #include<stdio.h>
// #include<string.h>
// #include<sys/types.h>
// #include<sys/stat.h>
// #include<fcntl.h>
// #include<unistd.h>
// #include<stdlib.h>


// int main(int argc,char *argv[]){
//     int fd ;
//     char arr1[100];
//     char *path = "/home/saurabh/Documents/OS/lo";
//     // if((mknod(path,S_IFIFO|0666,0))<0){
//     //     perror("Error");
//     //     exit(0);
//     // }
//     memset(arr1,'\0',sizeof(arr1));
//     fd = open(path,O_RDONLY,0);
//     if(fd<0){
//         perror("Can't open\n");
//         exit(0);
//     }
//     while((read(fd,arr1,sizeof(arr1)))<0){
//         continue;
//     }
//     printf("User 2: %s",arr1);
//     close(fd);

//     remove(path);
//     return 0;

    
// }






#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(int argc,char**argv) 
{ 
	int fd; 

	// FIFO file path 
	char * myfifo = "/home/saurabh/Documents/OS/as3"; 

	
	// mkfifo(<pathname>, <permission>) 
	mkfifo(myfifo, 0666); 

	char arr1[80], arr2[80]; 

	 
    fd = open(myfifo, O_WRONLY); 
    //fgets(arr2, 80, stdin); 
    write(fd, argv[1], strlen(argv[1])+1); 
    close(fd); 

    fd = open(myfifo, O_RDONLY); 
    read(fd, arr1, sizeof(arr1)); 
    printf("User2: %s\n", arr1); 
    close(fd); 
    
	return 0; 
} 









