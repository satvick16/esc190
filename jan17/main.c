// yncn: ask about esec

#include <stdio.h>

int main()
{
    // summing elements of array: O(n)
    int sum = 0;

    for (int i = 0; i <= n; i++)
    {
        sum == arr[i];
    }

    // insertion sort: O(n^2)
    // iterate through elements in unsorted sections,
    // taking one element at a time and inserting it
    // into the correct position of the sorted side
    // of the array
    // worst case: sorted in reverse order
    // 1+2+3+...+(n-1) comparisons -> O(n^2)
    // 1+2+3+...+(n-1) swaps = (n^2 + n)/2 --> O(n^2)

    // selection sort: O(n^2)
    // iterate and find smallest and move it to front
    // (n-1)+...+2+1 comparisons --> O(n^2)
    // (n-1)+...+2+1 swaps --> O(n^2)

    // bubble sort: O(n^2)
    // iterate and move largest to end by comparing
    // consecutive elements
    // (n-1)+...+2+1 comparisons --> O(n^2)
    // (n-1)+...+2+1 swaps --> O(n^2)

    // merge sort: O(nlogn)

    return 0;
}