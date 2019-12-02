#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(int argc, char**argv) 
{ 
	int fd; 

	// FIFO file path 
	char * myfifo = "/home/saurabh/Documents/OS/as3"; 

	
	// mkfifo(<pathname>, <permission>) 
	//mkfifo(myfifo, 0666); 

	char arr1[100]; 
	 
    fd = open(myfifo, O_RDONLY); 
    while((read(fd, arr1, sizeof(arr1)))<0){
        continue;
    }
    printf("User1: %s\n", arr1); 
    close(fd); 

    char *arr2 = "ACK";
    fd = open(myfifo,O_WRONLY);
    printf("Sending ACK\n");
    write(fd,arr2,(strlen(arr2)+1));
    close(fd);
    
	return 0; 
} 
