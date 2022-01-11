#include <stdio.h>
#include "lab1.h"

int main()
{
    // testing part 1
    double test_p1 = split_bill(50.01, 0.13, 0.15, 2);
    printf("The split will be: $%.2f\n", test_p1);

    // testing part 2
    double test_p2 = adjust_price(25.00);
    printf("The adjusted price is: $%.2f\n", test_p2);

    // testing part 3
    char test_food[] = "Three Cheese Pizza";
    int test_p3 = sandy_eats(test_food);
    if (test_p3 == 0)
    {
        printf("Sandy would NOT eat %s.\n", test_food);
    }
    else
    {
        printf("Sandy would eat %s.\n", test_food);
    }

    // testing part 4
    char test_p4[] = "zebra";
    imagine_fish(test_p4);
    printf("Just imagine, a %s!\n", test_p4);

    return 0;
}