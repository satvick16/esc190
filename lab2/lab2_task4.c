#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = (int *)malloc(sizeof(int));
    printf("Value stored at address %p: %d\n", p, *p);

    *p = 1;
    printf("Value stored at adddress %p: %d\n", p, *p);

    free(p);
    printf("Value stored at adddress %p: %d\n", p, *p);

    return 0;
}