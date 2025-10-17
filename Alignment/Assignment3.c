#include <stdio.h>
#include <stdlib.h>

struct myStr {
    char a;
    int b;
    double c;
};

#pragma pack(1)
struct pragmaStr {
    char a;
    int b;
    double c;
};

int main() {
    struct myStr str1;
    struct pragmaStr str2;

    printf("Size of the original struct: %lu\n", sizeof(str1));
    printf("Address of a: %p\n", &str1.a);
    printf("Address of b: %p\n", &str1.b);
    printf("Address of c: %p\n", &str1.c);

    printf("\n");

    printf("Size of the packed struct with 1: %lu\n", sizeof(str2));
    printf("Address of a: %p\n", &str2.a);
    printf("Address of b: %p\n", &str2.b);
    printf("Address of c: %p\n", &str2.c);

    return 0;
}
