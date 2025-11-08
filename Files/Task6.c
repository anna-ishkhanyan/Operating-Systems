#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char *file_name = "numbers.txt";                  // file name
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644); // create ot overwrite file
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }

    for (int i = 1; i <= 10; i++) {                  // write numbers 1 to 10
        char line[8];
        int len = snprintf(line, sizeof(line), "%d\n", i); // convert number to string
        write(fd, line, len);                        // write line to file
    }
    close(fd);                                        // close file

    fd = open(file_name, O_RDWR);                     // reopen file for read/write
    if (fd < 0) { 
        perror("open"); 
        return 1; 
    }

    off_t offset = 0;                                 // position after 3rd line
    int newline_count = 0;
    char c;

    while (read(fd, &c, 1) == 1) {                   // read char by char
        if (newline_count == 3) 
            break;
        offset++;
        if (c == '\n') newline_count++;
    }

    off_t rest_start = offset;                        // start of remaining data
    lseek(fd, rest_start, SEEK_SET);                 
    char remainder[512];
    ssize_t rem_size = read(fd, remainder, sizeof(remainder)); // read remaining content
    if (rem_size < 0) { 
        perror("read remainder"); 
        close(fd); 
        return 1; 
    }

    lseek(fd, offset, SEEK_SET);                      // go to insert position
    const char *new_text = "100\n";                  
    write(fd, new_text, strlen(new_text));           // insert new line
    write(fd, remainder, rem_size);                  // write back remaining data
    ftruncate(fd, offset + strlen(new_text) + rem_size); // change file size
    close(fd);                                        // close file

    fd = open(file_name, O_RDONLY);                  // reopen for reading
    if (fd < 0) { 
        perror("open"); 
        return 1;
    }

    printf("final file content:\n");
    while (read(fd, &c, 1) == 1) write(1, &c, 1);   // print file content
    close(fd);

    return 0;
}
