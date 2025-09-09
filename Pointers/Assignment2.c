#include <stdio.h>

int main(){
	int arr[] = {0,1,2,3,4};
	int *p = arr;
	printf("\n %s", "Printing the original array: ");
	for(int i = 0; i < 5; i++){
		printf("%d ", *p);
		p++;
	}
	p = arr;
	printf("\n %s", "Printing the changed array: ");
	for(int i = 0; i < 5; i++){
		(*p)++;
		printf("%d ", *p);
		p++;
	}
        printf("\n %s", "Printing using array name: ");
	for (int i = 0; i < 5; i++){
		printf("%d ", arr[i]);
	}
	return 0;

}
