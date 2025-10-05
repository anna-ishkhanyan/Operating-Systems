#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int sum = 0;
    int *arr =(int*) calloc(n, sizeof(int));
    
    if(!arr){
        return 1;
    }
    
    printf("Array after calloc: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        sum = sum + arr[i];
    }
    printf("\n");

    printf("Updated array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    printf("Average of the array %.2f\n", (float)sum/n);
    free(arr);
    return 0;
}