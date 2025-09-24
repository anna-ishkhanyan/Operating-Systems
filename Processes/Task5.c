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
        printf("CHILD'S PID=%d\n", getpid());
        exit(0);
    }
    else {
        printf("PARENT'S PID = %d\n", getpid());
        sleep(60);
    }
    return 0;
}
