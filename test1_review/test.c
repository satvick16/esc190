#include <stdio.h>
#include <stdlib.h>

void insert(int **arr, int *size, int *n, int i, int new)
{
    if (size == n)
    {
        *arr = realloc(*arr, 2 * (*size) * sizeof(int));
        (*size) *= 2;
    }

    int temp = 0;

    for (int x = i; x < (*n); x++)
    {
        (*arr)[x] = temp;
        temp = (*arr)[x + 1];
        (*arr)[x + 1] = (*arr)[x];
    }

    (*n)++;

    (*arr)[i] = new;
}

int main()
{
    // int *arr = (int *)malloc(5 * sizeof(int));
    // arr[0] = 0;
    // arr[1] = 0;
    // arr[2] = 0;
    // arr[3] = 0;
    // arr[4] = 0;

    // printf("here\n");

    // int *size = (int *)malloc(sizeof(int));
    // *size = 5;
    // int *n = (int *)malloc(sizeof(int));
    // *n = 5;

    // insert(&arr, size, n, 3, 1);

    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%d\n", arr[i]);
    // }

    int x = 99L;
    printf("%d\n", x);

    return 0;
}