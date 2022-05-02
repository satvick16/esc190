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
    // check if full
    if (bt->size == bt->count)
    {
        bt->tree = realloc(bt->tree, sizeof(int) * (bt->size) * 2);
        bt->size = (bt->size) * 2;
    }
    // insert value
    (bt->tree)[bt->count] = val;
    (bt->count)++;
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

    int nodes[] = {3, 5, 4, 1, 6, 12, 9, 7, -1};
    for (int i = 0; nodes[i] != -1; i++)
    {
        insert(bt, nodes[i]);
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