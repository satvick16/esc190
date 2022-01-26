#include <stdlib.h>

int main()
{
    // void *malloc(size_t size)
    // allocates a block of (uninitialized) memory, size specifies the block size

    // void *calloc(size_t nmemb, size_t size)
    // allocates a block of memory, nmemb * size, each initialized to 0

    // if a memory block cannot be allocated, null ptr is returned

    // void *realloc(void *ptr, size_t size)
    // resizes the block of memory pointed to by ptr
    // ptr should point to a memory block from prior malloc(), calloc(), realloc()
    // if ptr is null, this becomes malloc()
    // new size of memory block is size
    // if size is 0, this becomes free()

    // void free(void *ptr)
    // frees the memory block ptr points to
    // if ptr is null, nothing happens

    int n = 5;
    int *ptr_a = malloc(n * sizeof(int)); // treat like array[5]
    int *ptr_b = calloc(n, sizeof(int));  // treat like array[5] = {0}

    int *another = ptr_b;

    free(ptr_a);
    free(another);

    return 0;
}