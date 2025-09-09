#include <stdio.h>

int main(){
	int a = 5;
	int *p1 = &a;
	int **p2 = &p1;
	printf("%s %d", "Using single pointer: ", *p1);
	printf("\n%s %d\n", "Using double pointer: ", **p2);
	return 0;
}
