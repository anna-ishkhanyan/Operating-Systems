#include <stdio.h>

int main(){
	char str[] = "Hello";
	char *first = &str[0];
	int count = 0;

	while (*first) {
		printf("%c", *first);
		first++;
		count++;
	}
	printf("\n%s%d\n", "Number of characters: ", count);
	return 0;
}
