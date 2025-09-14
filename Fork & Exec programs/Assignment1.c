#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t pid = fork(); // creates a child process
	if (pid < 0) // fails to create
		perror("fork"); 
	else if (pid == 0){ // child process
		int ret; // used the textbook for this strucure, so we just
		ret = execl("/bin/ls", "ls", ".",NULL); // use execl which replaces the current process image with a new one by loading into memory the progeam we mentioned in the past, then we mentioned the command ls, then the current directory, then NULL as the argument list of execl has to be null terminated
		if (ret == -1) // fails 
			perror ("execl"); 
	}
	wait(NULL); // if its the parent process, waits until the child is finished and prints the message
	printf("Parent process done\n");
	
	return 0;
}
