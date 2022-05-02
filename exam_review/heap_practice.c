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

// new function - removing
void remove_min(bin_tree *bt);
// new helper functions to make a min heap
void swap_up(bin_tree *bt, int cindex);
void swap_down(bin_tree *bt, int pindex);

// initialize complete binary tree
bin_tree *plant_bt(int rval)
{
    // allocate memory for tree
    bin_tree *bt = (bin_tree *)malloc(sizeof(bin_tree));
    // setting the root and more
    bt->tree = (int *)malloc(sizeof(int));
    (bt->tree)[0] = rval;
    bt->size = 1;
    bt->count = 1;
    return bt;
}

// insert value
void insert(bin_tree *bt, int val)
{
    // add to end and bubble up
    bt->count++;

    if (bt->size < (bt->count))
    {
        bt->tree = realloc(bt->tree, sizeof(int) * (bt->count) * 2);
    }

    bt->tree[bt->count - 1] = val;
    swap_up(bt, bt->count - 1);
}

// compare child with parent, swap up if needed
void swap_up(bin_tree *bt, int cindex)
{
    // stopping condition
    if (cindex == 0)
    {
        return;
    }

    // calculate parent index
    int pindex = (cindex - 1) / 2;

    if (bt->tree[cindex] < bt->tree[pindex])
    {
        int temp = bt->tree[pindex];
        bt->tree[pindex] = bt->tree[cindex];
        bt->tree[cindex] = temp;

        swap_up(bt, temp);
    }
    return;
}

// remove min (root node for a min heap)
void remove_min(bin_tree *bt)
{
    // bring end to top
    bt->tree[0] = bt->tree[bt->count - 1];
    bt->count--;

    // bubble down
    swap_down(bt, 0);
}

// compare parent and two children, swap down if needed
void swap_down(bin_tree *bt, int pindex)
{
    // get child indices
    int lindex = 2 * pindex + 1;
    int rindex = 2 * pindex + 2;

    // stopping condition
    if (lindex + 1 > bt->count)
    {
        return;
    }

    if (lindex < pindex)
    {
        int temp = bt->tree[lindex];
        bt->tree[lindex] = bt->tree[pindex];
        bt->tree[pindex] = temp;

        swap_down(bt, lindex);
    }
    else
    {
        if (rindex + 1 < bt->count)
        {
            int temp = bt->tree[rindex];
            bt->tree[rindex] = bt->tree[pindex];
            bt->tree[pindex] = temp;

            swap_down(bt, rindex);
        }
    }

    return;
}

// look for value
int search(bin_tree *bt, int val)
{
    // iterate through array to look for value
    for (int i = 0; i < bt->count; i++)
    {
        if ((bt->tree)[i] == val)
        {
            printf("Found %d!\n", val);
            return 1;
        }
    }

    // not found
    printf("%d not found \n", val);
    return 0;
}

// free memory allocated
void free_bt(bin_tree *bt)
{
    free(bt->tree);
    free(bt);
}

int main()
{
    // building the tree from L17, slide 7
    bin_tree *bt = plant_bt(2);
    print_bt(bt);
    search(bt, 5);

    // insert into min heap
    int nodes[] = {3, 5, 4, 1, 6, 12, 9, 7, -1};
    for (int i = 0; nodes[i] != -1; i++)
    {
        insert(bt, nodes[i]);
        print_bt(bt);
    }
    search(bt, 5);

    // remove from min heap
    for (int i = 0; i < 9; i++)
    {
        remove_min(bt);
        print_bt(bt);
    }
    search(bt, 5);

    free_bt(bt);
    bt = NULL;
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