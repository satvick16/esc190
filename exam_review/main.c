#include <stdio.h>

int main()
{
    char *names[] = {"Jim", "Jack", "Joe"};
    int i;

    for (i = 0; i < 3; ++i)
    {
        printf("%d\n", i);
        printf(" %s", names[i]);
    }

    return 0;
}