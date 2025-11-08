#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char from[256], to[256], buff[4096]; // file names and buffer
    int fd_in, fd_out; // file desriptors
    ssize_t n, total = 0; // bytes read and written and total count


    printf("inout the source file: ");
    if (scanf("%255s", from) != 1) 
        return 1;
    printf("destination file: ");
    if (scanf("%255s", to) != 1) 
        return 1;

    if ((fd_in = open(from, O_RDONLY)) < 0) { 
        perror("opening the source"); 
        return 1; 
    }
    if ((fd_out = open(to, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror("opening the dest"); close(fd_in); return 1;
    }

    while ((n = read(fd_in, buff, sizeof(buff))) > 0) {
        if (write(fd_out, buff, n) != n) {  // write to destination
            perror("write"); 
            return 1; 
        }
        total += n; // counting total bytes copied
    }
    if (n < 0) 
        perror("read");

    printf("Total number of the bytes copied: %zd\n", total);
    close(fd_in);  // closing fds
    close(fd_out);
    return 0;
}
