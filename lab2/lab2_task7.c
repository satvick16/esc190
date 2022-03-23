#include <stdio.h>
#include <stdlib.h>

void append(int *x, int *n, int val)
{
    x = realloc(x, (*n + 1) * sizeof(int));
    *(x + *n) = val;
    (*n)++;
}

int main()
{
    int *arr = (int *)malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        arr[i] = 0;
    }

    int n = 5;
    int val = 1;

    append(arr, &n, val);

    printf("%d\n", n);

    for (int i = 0; i < 6; i++)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}