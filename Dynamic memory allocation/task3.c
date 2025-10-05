#include <stdio.h>
#include <stdlib.h>

int main(){
    int *arr =(int*) malloc(10 * sizeof(int));
    
    if(!arr){
        return 1;
    }

    printf("Enter 10 integers: ");
    for (int i = 0; i < 10; i++)
        scanf("%d", &arr[i]);
    

    int *reallocated = realloc(arr, 5* sizeof(int));
     if(!reallocated){
        free(arr);
        return 1;
    }
    arr = reallocated;
    printf("Array after resizing: ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}