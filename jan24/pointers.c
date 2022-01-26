#include <stdio.h>

int main()
{
    int x = 5;
    int *y;  // stores address of an int
    int **z; // stores address of an int

    int x = 5;
    int *y = &x;  // address of x will be stored in y
    int **z = &y; // address of y will be stored in z

    printf("address of x: %p\n", &x);
    printf("address of x: %p\n", y);

    // * is also used as dereferencing operator
    printf("value at &x: %d\n", x);
    printf("value at &x: %d\n", *y);
    printf("value at &x: %d\n", **z);
    printf("value at &x: %d\n", *(&x));

    int x = 5;
    int *y = &x;
    *y = 10; // same as x = 10

    // avoid: no initial value assigned to y
    int *y;
    printf("%d\n", *y);
    *y = 5;

    int arr[] = {1, 2, 3, 4, 5};
    *arr = 5;
    int *arr_ptr = arr;

    return 0;
}