#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid = fork();

    if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0){
        printf("1 CHILD'S PID = %d\n", getpid());
        exit(8);
    }
    else {
        int statloc_1;
        wait(&statloc_1);
        if (WIFEXITED(statloc_1)){
            printf("Exit status of the first child: %d\n", WEXITSTATUS(statloc_1));
        }
        pid_t second = fork();

        if (second < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (second == 0){
            printf("2 CHILD'S PID = %d\n", getpid());
            exit(9);
        }
        else { 
            int statloc;
            waitpid(second, &statloc, 0);
            if (WIFEXITED(statloc)){
                printf("Exit status of the second child: %d\n", WEXITSTATUS(statloc));
            }
            printf("PARENT'S PID = %d\n", getpid());
        }
    }
    return 0;
}
// Acknowlegment: used code chunks as reference from linux programming boook (R.Love)
