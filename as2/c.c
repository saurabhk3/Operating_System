
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
    // Compile and link with -pthread
    //int pthread_join(pthread_t thread, void **retval);

#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>

void * my_thread(void * myarg){
    printf("HELLO WORLD!\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t thread ;
    pthread_create(&thread,NULL,my_thread,NULL);
    pthread_join(thread,NULL);  //join with the terminated thread my_thread
    return 0;
}
