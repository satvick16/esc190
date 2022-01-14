#include <stdio.h>
#include <string.h>

// char* indicates string can be modified by function
char *strcpy(char *s1, const char *s2);
int strlen(const char *s); // omits '\0'
char *strcat(char *s1, const char *s2);
int strcmp(const char *s1, const char *s2); // returns an int that indicates if s1 is >, =, or < than s2

int main()
{
    // strings in C are just character arrays that end in null character '\0'
    // null evaluates to false (0)
    // "c" vs. 'c'

    // when storing a string, make sure you include space for the null character

    char my_array[] = "hello world"; // mutable
    char *my_ptr = "hello world";    // immutable

    return 0;
}