#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "lab1.h"

double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people)
{
    double total = base_amount;
    total *= (1 + tax_rate);
    total *= (1 + tip_rate);
    total = roundf(total * 100) / 100;

    double split = total / num_people;
    split = roundf(split * 100) / 100;

    return split;
}

double adjust_price(double original_price)
{
    return 10 * pow(original_price, 0.5);
}

int sandy_eats(char menu_item[])
{
    int length = strlen(menu_item);

    if (length % 2 != 0)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        menu_item[i] = tolower(menu_item[i]);
    }

    char *ptr1 = strstr(menu_item, "j");
    char *ptr2 = strstr(menu_item, "k");
    char *ptr3 = strstr(menu_item, "l");
    char *ptr4 = strstr(menu_item, "fish");

    return !(ptr1 || ptr2 || ptr3 || ptr4);
}

void imagine_fish(char thing[])
{
    strcat(thing, "fish");
}