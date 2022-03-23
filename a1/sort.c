#include <stdio.h>

void print_list(int arr[])
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void insertion_sort()
{
    int arr[] = {1, 3, 5, 2, 3, 6, 7, 1, 9, 4};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        int j = i;

        while (j > 0 && arr[j] < arr[j - 1])
        {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
    }

    print_list(arr);
}

void selection_sort()
{
    int arr[] = {1, 3, 5, 2, 3, 6, 7, 1, 9, 4};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        int min = i;

        for (int j = i + 1; j < sizeof(arr) / sizeof(arr[0]); j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    print_list(arr);
}

void bubble_sort()
{
    int arr[] = {1, 3, 5, 2, 3, 6, 7, 1, 9, 4};

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if (arr[j] > arr[j - 1])
            {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

void merge(int *left, int *right, int size_left, int size_right)
{
    int *new = (int *)malloc(sizeof(int) * 10);
    int a = 0;
    int b = 0;

    int counter = 0;

    while (a < size_left && b < size_right)
    {
        if (left[a] < right[b])
        {
            new[counter] = left[a];
            a++;
        }
        else
        {
            new[counter] = right[b];
            b++;
        }

        counter++;
    }

    if (a == size_left)
    {
        for (int i = b; i < size_right; i++)
        {
            new[counter] = right[i];
            counter++;
        }
    }
    else
    {
        for (int i = a; i < size_left; i++)
        {
            new[counter] = left[i];
            counter++;
        }
    }
}

void mergesort(int *arr)
{
    int len = 10;

    int mid = len / 2;

    int *left = (int *)malloc((mid + 1) * sizeof(int));
    int *right = (int *)malloc((len - 1 - mid) * sizeof(int));

    for (int i = 0; i < len; i++)
    {
        if (i < mid + 1)
        {
            left[i] = arr[i];
        }
        else
        {
            right[i - (mid + 1)] = arr[i];
        }
    }

    mergesort(left);
    mergesort(right);

    merge(left, right);
}

void partition(int **a, int low, int high)
{
    pivot = (*a)[low];
    leftwall = low;

    for (int i = low + 1; i < high; i++)
    {
        if ((*a)[i] < pivot)
        {
            int temp = a[leftwall];
            a[leftwall] = a[i];
            a[i] = temp;

            leftwall++;
        }
    }

    int temp = a[leftwall];
    a[leftwall] = a[pivot];
    a[pivot] = temp;

    return leftwall;
}

void quicksort(int **a, int low, int high)
{
    if (low < high)
    {
        pivot = partition(a, low, high);
        quicksort(a, low, pivot);
        quicksort(a, pivot + 1, high);
    }
}

int **initStructure(int r, int *a)
{
    int **ret = (int **)malloc(r * sizeof(int *));

    for (int i = 0; i < r; i++)
    {
        ret[i] = (int *)calloc(a[i], sizeof(int));
    }

    return ret;
}

void append(int **x, int *n, int val)
{
    *x = realloc(*x, sizeof(int) * (*n + 1));
    *(*x + n) = val;
    (*n)++;
}

int main()
{
    return 0;
}