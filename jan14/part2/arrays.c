#include <stdio.h>

void doubler(int x[], int arr_len)
{
    for (int i = 0; i < arr_len; i++)
    {
        x[i] *= 2;
    }
}

int main()
{
    int my_array[10];
    my_array[0] = 5;

    int my_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // remaining elements are set to 0
    int my_array[10] = {0};

    return 0;
}