#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int sum = 0;
    int *arr =(int*) malloc(sizeof(int) * n);
    
    if(!arr){
        return 1;
    }
    
    printf("Enter %d integers: ", n);

    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        sum = sum + arr[i];
    }

    printf("Sum of the array: %d\n", sum);
    free(arr);
    return 0;
}