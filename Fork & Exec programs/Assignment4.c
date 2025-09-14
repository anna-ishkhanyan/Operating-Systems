#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t pid = fork();
	
	if (pid < 0){
		perror("fork");
	    exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		int ret = execl("/bin/grep", "grep", "bla","test.txt", NULL);
		if (ret < 0){
			perror("grep");
		    exit(EXIT_FAILURE);
		}
	}

	wait(NULL);
	printf("Parent process completed");
}
