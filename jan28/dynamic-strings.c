#include <stdio.h>
#include <string,.>

char *new_cat(const char *first, const char *second)
{
    char *cat_str;
    cat_str = malloc(strlen(first) + strlen(second) + 1);

    if (cat_str == NULL)
    {
        return cat_str;
    }

    strcpy(cat_str, first);
    strcat(cat_str, second);

    return cat_str;
}

int main()
{
    int n = 6;
    char *mystring = malloc(n + 1);
    strcpy(mystring, "Ar");
    strcat(mystring, "iel");

    return 0;
}