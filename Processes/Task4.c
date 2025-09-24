#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid1 == 0) {
        printf("Child 1 (PID=%d)\n", getpid());
        exit(5);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid2 == 0) {
        printf("Child 2 (PID=%d)\n", getpid());
        exit(10);
    }

    int statloc;
    for (int i = 0; i < 2; i ++){
        waitpid(-1, &statloc, 0);
        if (WIFEXITED(statloc)) {
                printf ("Normal termination with exit status=%d\n",
    WEXITSTATUS (statloc));
            } else if (WIFSIGNALED(statloc)) {
                printf("Killed by signal=%d\n", WTERMSIG (statloc));
            }
    }
    return 0;
}
