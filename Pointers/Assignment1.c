#include <stdio.h>

int main (){
	int a = 6;
	int *b = &a;
	printf("%s %p \n%s %p\n","Using the variable:", &a,"Using the pointer:", b);

	*b = 8;

	printf("%s %d\n", "Modified variable:", a);

	return 0;
}
