#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644); // open or create log file in append mode
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }

    char buf[256], out[300];                 // input and output buffers
    ssize_t n = read(0, buf, sizeof(buf) - 1); // read input from stdin
    if (n < 0) { 
        perror("read"); 
        close(fd); 
        return 1; 
    }
    buf[n] = '\0';                           // terminate string

    if (buf[n - 1] == '\n')                  // remove trailing newline
        buf[n - 1] = '\0';

    snprintf(out, sizeof(out), "PID=%d: %s\n", getpid(), buf); // format message with process ID

    if (write(fd, out, strlen(out)) < 0) {   // write message to file
        perror("write"); 
        close(fd); 
        return 1; 
    }

    off_t pos = lseek(fd, 0, SEEK_CUR);      // get current offset in file
    printf("Final offset: %lld\n", pos);      // print offset
    close(fd);                               // close file
    return 0;
}
