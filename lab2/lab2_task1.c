#include <stdio.h>

int main()
{
	int x = 0;
	int *ptr = &x;
	printf("x contains the value of %d at location %p\n", *ptr, ptr);

	return 0;
}