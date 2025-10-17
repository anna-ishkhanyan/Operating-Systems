#include <stdio.h>
#include <stdlib.h>

int main(){
    int a;
    char c;
    double d;
    short h;

    printf("Size of int: %lu, address: %p \n", sizeof(a), &a);
    printf("Size of char: %lu, address: %p \n", sizeof(c), &c);
    printf("Size of double: %lu, address: %p \n", sizeof(d), &d);
    printf("Size of short: %lu, address: %p \n", sizeof(h), &h);

    return 0;
}