#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	pid_t pid = fork();
	
	if (pid < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0){
		char arg[200];
		printf("Enter the argument to the command echo: ");
		scanf("%[^\n]", arg); // at first tried just by mentioning the max num of characters, but scanf was reading until the first whitespace so I found  a solution in https://forums.codeguru.com/showthread.php?181020-getting-a-whole...

		int ret = execl("/bin/echo", "echo", arg,  NULL);
		if (ret < 0){
			perror("execl");
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);
	printf("Parent process done\n");

	return 0;
}
