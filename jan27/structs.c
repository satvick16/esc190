#include <stdio.h>

struct pricetag
{
    double price = 0.99;
    double sale_price;
    char item_name[100];
};

int main()
{
    struct pricetag new_item = {10.99, 4.99, "Shelf"};
    pricetag.price = 0.25;

    struct pricetag *ptag_ptr;
    ptag_ptr = malloc(sizeof(struct pricetag));
    (*ptag_ptr).sale_price = 0.15;

    printf("sale price = %.2f\n", (*ptag_ptr).sale_price);
    printf("sale price = %.2f\n", ptag_ptr->sale_price);

    return 0;
}