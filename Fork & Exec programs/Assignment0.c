#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void check_pid(pid_t pid, int num) { // used the function from the textbook to add the necessary checks, also created this function to avoid writing redundant if blocks in main
    if (pid > 0) { // checks if the pid is larger than 0, that means that's the parent process
        printf("Number %d: I am the parent of pid=%d! PID=%d, PPID=%d\n", num, pid, getpid(), getppid());
    } else if (pid == 0) { // checks if it's the child process
        printf("Number %d: I am the baby! PID=%d, PPID=%d\n", num, getpid(), getppid());
    } else if (pid == -1) {
        perror("fork"); //checks for the errors, calls perror which prints the stderr output
    }
}

int main() {
    pid_t pid_1 = fork(); // creates the first process, now we have one parent and one child
    check_pid(pid_1, 1); // calls the function we created earlier

    pid_t pid_2 = fork(); // calls the second fork, now we have 4 processes, each one from the initial 2 processses we had
    check_pid(pid_2, 2);

    pid_t pid_3 = fork(); // and finally the same one here, we have 8 processes and the end
    check_pid(pid_3, 3);

    sleep(5);
    return 0;
}
