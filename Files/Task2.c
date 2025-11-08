#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char *file_name = "data.txt"; // name of the file
    int fd; // file descriptor
    char buff[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // bufffer with letters

    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);  // create or overwrite file
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }
    if (write(fd, buff, 26) != 26) { // write 26 bytes to file
        perror("write"); 
        close(fd); 
        return 1; 
    }
    close(fd); // closing the file

    fd = open(file_name, O_RDWR); // reopening file for read and write
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }

    off_t size = lseek(fd, 0, SEEK_END); // move to end to get size
    printf("Original size: %lld bytes\n", size);

    if (ftruncate(fd, 10) < 0) {  // truncate the  file to 10 bytes
        perror("ftruncate"); 
        close(fd); 
        return 1; 
    }

    off_t new_size = lseek(fd, 0, SEEK_END); // getting new size
    printf("New size: %lld bytes\n", new_size); 

    lseek(fd, 0, SEEK_SET); // move to start of file
    ssize_t n = read(fd, buff, sizeof(buff) - 1); // read file content
    if (n < 0) { 
        perror("read"); 
        close(fd); 
        return 1; 
    }
    buff[n] = '\0'; // adding null terminator
    printf("Content: %s\n", buff);

    close(fd); // closing the file
    return 0;
}
// Acknowledgment: used some code chunks and logic from Linux Programming by Robert Love by R. Love