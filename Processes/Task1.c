#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        printf("CHILD'S PID = %d\n", getpid());
        exit(0);
    }
    else{
        printf("PARENT'S PID = %d\n", getpid());
    }
    return 0;
}