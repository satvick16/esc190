#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// struct for our complete binary tree
typedef struct bin_tree
{
    int *tree;
    int size;
    int count;
} bin_tree;

// just for printing the demo, no need to study these two too closely...
// if you can write something more elegant, please send it to me!
void print_spaces(int num);
void print_bt(bin_tree *bt);

// functions for heapsort, new function: heapify()
int remove_min(bin_tree *bt); // now will return the min
void heapify(bin_tree *bt);
void swap_down(bin_tree *bt, int pindex);

// remove min (root node for a min heap)
int remove_min(bin_tree *bt)
{
    bt->tree[0] = bt->tree[bt->count - 1];
    bt->count--;
    swap_down(bt, 0);
}

// compare parent and two children, swap down if needed
void swap_down(bin_tree *bt, int pindex)
{
    int lindex = 2 * pindex + 1;
    int rindex = 2 * pindex + 2;

    if (lindex > bt->count)
    {
        return;
    }

    if (lindex < rindex)
    {
        if (bt->tree[pindex] > bt->tree[lindex])
        {
            int temp = bt->tree[pindex];
            bt->tree[pindex] = bt->tree[lindex];
            bt->tree[lindex] = temp;
        }

        swap_down(bt, lindex);
    }
    else
    {
        if (rindex < bt->count)
        {
            if (bt->tree[pindex] > bt->tree[rindex])
            {
                int temp = bt->tree[pindex];
                bt->tree[pindex] = bt->tree[rindex];
                bt->tree[rindex] = temp;
            }

            swap_down(bt, rindex);
        }
    }

    return;
}

void heapify(bin_tree *bt)
{
    // go backwards level by level
    // swap down
    for (int i = bt->count - 1; i >= 0; i--)
    {
        swap_down(bt, i);
    }
}

int main()
{
    int unsorted_arr[] = {2, 7, 12, 4, 1, 6, 5, 9, 3};
    int sorted_arr[9] = {0}, size = 16, count = 9;
    bin_tree bt = {unsorted_arr, size, count};
    // size here is a lie, just used for printing

    // print before and after heapify
    print_bt(&bt);
    heapify(&bt);
    print_bt(&bt);

    // extract min value and add to sorted array
    int min = 0;
    for (int i = 0; i < 9; i++)
    {
        min = remove_min(&bt);
        sorted_arr[i] = min;
    }

    // print sorted array
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", sorted_arr[i]);
    }
    printf("\n");
    return 0;
}

void print_spaces(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf(" ");
    }
}

void print_bt(bin_tree *bt)
{
    int row_end = 0, row_start = 0, lead_space = log2(bt->size) - 1, mid_space;
    printf("Printing bin_tree with %d nodes (array size: %d):\n",
           bt->count, bt->size);
    for (int i = 0; i < bt->count; i++)
    {
        if (i == row_start)
        {
            print_spaces(pow(2, lead_space));
            row_start = row_start * 2 + 1;
        }
        printf("%d", (bt->tree)[i]);
        if (i == row_end)
        {
            printf("\n");
            row_end = row_end * 2 + 2;
            mid_space = pow(2, lead_space) - 1;
            lead_space--;
        }
        else
        {
            print_spaces(mid_space);
        }
    }
    printf("\n");
}