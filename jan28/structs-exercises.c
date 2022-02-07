#include <stdio.h>
#include <math.h>

struct Point
{
    double x;
    double y;
};

double euclidean_dist(struct Point p1, struct Point p2)
{
    return pow(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2), 0.5);
}

struct FancyList
{
    int *ptr;
    int max_el;
    int count_el;
};

// set up a FancyList variable with an empty list
// that holds (max_el = n) elements
// dynamically allocate for ptr
// when appending, check if list is full and double
// the size
// print the list contents

void append(struct FancyList fl, int val)
{
    fl->count_el++;

    if (fl->count_el == fl->max_el)
    {
        fl->max_el *= 2;
        fl->ptr = realloc(fl->ptr, sizeof(int) * fl->max_el);
    }

    fl->ptr[fl->count_el] = val;
}

void printfl(struct FancyList fl)
{
    for (int i = 1, i <= fl->count_el; i++)
    {
        printf("%d\n", fl->ptr[i - 1]);
    }
}

int main()
{
    int *p;
    struct FancyList fl
    {
        p, 1, 0
    };

    return 0;
}