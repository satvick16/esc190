int main()
{
    int arr[] = {1, 2, 3, 4, 5}, *arr_ptr;
    arr_ptr = arr;         // arr[0]
    arr_ptr = arr_ptr + 2; // arr[2]
    arr_ptr = arr_ptr - 2; // arr[1]

    *(arr + 3) = 5;     // arr[3] = 5
    *(arr_ptr + 2) = 6; // arr[3] = 6

    int *arr_ptr, *another, ptr_sub;

    arr_ptr = arr + 3;           // arr_ptr = &arr[3]
    another = arr_ptr - 2;       // another = &arr[1]
    ptr_sub = arr_ptr - another; // ptr_sub is 2
}