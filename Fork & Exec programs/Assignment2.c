#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	pid_t pid1 = fork(); // creates the first child process
	if (pid1 < 0){ // fails to create
                perror("fork");
	        	exit(EXIT_FAILURE);
	}
    else if (pid1 == 0){ // child process
		int ret; 
        ret = execl("/bin/ls", "ls", ".",NULL);
        if (ret == -1){
			perror ("execl");
		    exit(EXIT_FAILURE);
		}
    }
        
	pid_t pid2 = fork(); // creates the second child process
    if (pid2 < 0){ // fails to create
		perror("fork");
		exit(EXIT_FAILURE);
	}
    else if (pid2 == 0){ // child process
		int ret; 
        ret = execl("/bin/date", "date",NULL);
		if (ret == -1){
			perror ("execl");
			exit(EXIT_FAILURE);
		}
    }
	wait(NULL);
	wait(NULL); // as we have two child processes
    printf("Parent process done\n");
    
	return 0;
}
