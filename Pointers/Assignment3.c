#include <stdio.h>

void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}
int main(){
	int a = 5;
	int b = 6;
	printf("%s %d %d", "Original values: ", a, b);
	swap(&a, &b);
	printf("\n%s %d %d\n", "Modified values: ", a, b);

	return 0;
}
