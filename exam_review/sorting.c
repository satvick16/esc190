#include <stdio.h>

void insertion_sort()
{
    for (int i = 1; i < len; i++)
    {
        int j = i;

        while (arr[j] < arr[j - 1] && j > 0)
        {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;

            j--;
        }
    }
}

void selection_sort()
{
    for (int i = 0; i < len; i++)
    {
        int min_idx = i;

        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void bubble_sort()
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    return 0;
}