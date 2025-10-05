#include <stdio.h>
#include <stdlib.h>

int main() {
    char **arr = (char**) malloc(3 * sizeof(char*));
    if (!arr) 
        return 1;

    for (int i = 0; i < 3; i++) {
        arr[i] = (char*) malloc((50 + 1) * sizeof(char)); // +1 for the null terminator
        if (!arr[i]) 
            return 1;
    }

    printf("Enter %d strings:\n", 3);
    for (int i = 0; i < 3; i++)
        scanf("%50s", arr[i]);

    char **reallocated = realloc(arr, 5 * sizeof(char*));
    if (!reallocated) {
        for (int i = 0; i < 3; i++) 
            free(arr[i]);
        free(arr);
        return 1;
    }
    arr = reallocated;

    for (int i = 3; i < 5; i++) {
        arr[i] = (char*) malloc((50 + 1) * sizeof(char));
        if (!arr[i]) 
            return 1;
    }

    printf("Enter %d more strings:\n", 2);
    for (int i = 3; i < 5; i++)
        scanf("%50s", arr[i]);

    printf("All strings:\n");
    for (int i = 0; i < 5; i++)
        printf("%s, ", arr[i]);

    for (int i = 0; i < 5; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
