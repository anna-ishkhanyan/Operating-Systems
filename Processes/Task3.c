#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void func1(){
    printf("This message is the first one\n");
}

void func2(){
    printf("This message is the second one\n");
}

int main(){
    // exit(0); // obviously, the program ends here
    atexit(func1);
    // exit(0); // only the first funciton done at exit
    atexit(func2); // will be executed first
    // exit(0); // when we have exit() here, we have only two functions executued, without the following printf
    printf("just printing some things, then doing the function calls\n");
    return 0;
}
