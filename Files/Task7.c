#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    char f1[256], f2[256];                      // file names
    printf("first file: "); scanf("%255s", f1); // read first file name
    printf("second file: "); scanf("%255s", f2); // read second file name

    int fd1 = open(f1, O_RDONLY), fd2 = open(f2, O_RDONLY); // open both files
    if (fd1 < 0 || fd2 < 0) { 
        perror("open"); 
        return 1; 
    }

    unsigned char b1, b2;                        // bytes for comparison
    off_t i = 0;                                  // byte index
    ssize_t n1, n2;                               // read return values

    while (1) {
        n1 = read(fd1, &b1, 1);                  // read one byte from first file
        n2 = read(fd2, &b2, 1);                  // read one byte from second file

        if (n1 == 0 && n2 == 0) {    
            printf("files are the same \n");
            break;
        }
        if (n1 != n2 || b1 != b2) {              // finding difference
            printf("files differ at byte %lld\n", i);
            close(fd1); close(fd2);
            return 1;
        }
        i++;                                     // icnrease byte index
    }

    close(fd1); 
    close(fd2);
    return 0;
}
