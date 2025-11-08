#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    char path[256]; // file path and character buffer
    char c;
    printf("inout file path: ");
    scanf("%255s", path); // read file path from user

    int fd = open(path, O_RDONLY); // opening the file for reading
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }

    int size = lseek(fd, 0, SEEK_END); // find file size
    if (size < 0) { 
        perror("lseek"); 
        close(fd); 
        return 1; 
    }

    if (size == 0) {  // if file is empty printing a newline
        write(1, "\n", 1); 
        close(fd); 
        return 0; 
    }

    for (int i = size - 1; i >= 0; i--) { // go through file backwards
        if (lseek(fd, i, SEEK_SET) < 0) {
            perror("lseek"); 
            break; 
        }
        if (read(fd, &c, 1) != 1) { 
            perror("read"); 
            break; 
        }
        write(1, &c, 1); // print character to stdout
    }
    write(1, "\n", 1); // final newline
    close(fd);  // close file
    return 0;
}
