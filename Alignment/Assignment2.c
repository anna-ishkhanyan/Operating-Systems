#include <stdio.h>
#include <stdlib.h>

struct mystruct {
    char a;
    int b;
    double c;
};

struct mystruct_second {
    double c;
    int b;
    char a;
};

int main() {
    struct mystruct str1;
    struct mystruct_second str2;

    printf("Size of the intial struct: %lu\n", sizeof(str1));
    printf("Address of a: %p\n", &str1.a);
    printf("Address of b: %p\n", &str1.b);
    printf("Address of c: %p\n", &str1.c);
    printf("\n");
    printf("Size of the second struct: %lu\n", sizeof(str2));
    printf("Address of c: %p\n", &str2.c);
    printf("Address of b: %p\n", &str2.b);
    printf("Address of a: %p\n", &str2.a);

    return 0;
}
