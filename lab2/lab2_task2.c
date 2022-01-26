#include <stdio.h>

int main()
{
    int x = 0;
    int y = x;

    int *ptr_x = &x;
    int *ptr_y = &y;
    int **pptr_x = &ptr_x;
    int **pptr_y = &ptr_y;

    ptr_x = &y;

    printf("%p\n", &x);
    printf("%p\n", &y);

    printf("x contains the value %d at location %p\n", *ptr_x, ptr_x);
    printf("y contains the value %d at location %p\n", *ptr_y, ptr_y);

    return 0;
}