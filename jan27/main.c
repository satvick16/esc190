#include <stdio.h>

int main()
{
    int n = 5;
    int *ptr_a = malloc(n * sizeof(int)); // uninitialized
    int ptr_b = calloc(n, sizeof(int));   // initialized
    int *another = ptr_b;

    free(ptr_a);
    free(another);

    ////

    int n = 4;
    int *ptr_b = calloc(n, sizeof(int));
    int *another = ptr_b;
    ptr_b = realloc(ptr_b, 2 * sizeof(int));
    another = ptr_b;
    ptr_b = realloc(ptr_b, 6 * sizeof(int));
    another = ptr_b;

    free(ptr_b);

    ////

    int **x = (int **)malloc(sizeof(int *) * 5);

    for (int i = 0; i < 5; i++)
    {
        *(x + i) = (int *)calloc(2, sizeof(int));
    }

    return 0;
}