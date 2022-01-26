#include <stdio.h>
#include "aheader.h"

int add(int x, int y)
{
    int z = x + y;
    x = 200;
    return z;
}

int multiply(int x, int y)
{
    int result = 0;
    for (int i = 0; i < y; i++)
    {
        result = add(result, x);
    }
    return result;
}