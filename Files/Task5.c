#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char *file_name = "sparse.bin";                 // name of the sparse file
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644); // create or overwrite file
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }

    write(fd, "START", 5);                          // write first part
    if (lseek(fd, 1024 * 1024, SEEK_CUR) < 0) {     // skip 1mb without writing
        perror("lseek"); 
        close(fd); 
        return 1; 
    }
    write(fd, "END", 3);                            // write last part
    close(fd);                                      // close file

    fd = open(file_name, O_RDONLY);                 // reopen file for reading
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }
    off_t size = lseek(fd, 0, SEEK_END);            // get file size
    printf("Apparent file size: %lld bytes\n", size); // print file size
    close(fd);                                      // close file

    return 0;
}
// Acknowledgment: used some code chunks and logic from Linux Programming by Robert Love by R. Love
