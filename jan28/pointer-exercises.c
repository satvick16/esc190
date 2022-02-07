#include <stdio.h>
#include <limits.h>

// swap two numbers
void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    // sort array
    int array[] = {1, 4, 2, 6, 4, 7, 4, 8, 2};
    int *ptr = array;

    int len = sizeof(array) / sizeof(array[0]);

    int new[len];

    for (int x = 0; x < len; x++)
    {
        int min = INT_MAX;
        int ind;

        for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
        {
            if (*(ptr + i) < min)
            {
                min = *(ptr + i);
                ind = i;
            }
        }

        new[x] = min;

        array = realloc(array, len - 1);
        array
    }

    // print array elements
    int *p = new;

    for (int i = 0; i < len; i++)
    {
        printf("%d\n", *(p + i));
    }

    return 0;
}