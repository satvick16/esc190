#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "lab1.h"

double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people)
{

    double total = (base_amount * (1 + tax_rate)) * (1 + tip_rate);
    double split_value = total / num_people;
    split_value = ((int)(split_value * 100)) / 100.0;

    if (split_value * num_people < total)
    {
        split_value += 0.01;
    }

    return split_value;
}

double adjust_price(double original_price)
{
    return 10 * pow(original_price, 0.5);
}

int sandy_eats(char menu_item[])
{
    if (strlen(menu_item) % 2 == 1)
    {
        return 0;
    }

    char *ptr1 = strstr(menu_item, "J");
    char *ptr2 = strstr(menu_item, "K");
    char *ptr3 = strstr(menu_item, "L");
    char *ptr4 = strstr(menu_item, "j");
    char *ptr5 = strstr(menu_item, "k");
    char *ptr6 = strstr(menu_item, "l");
    char *ptr7 = strstr(menu_item, "Fish");
    char *ptr8 = strstr(menu_item, "fish");

    return !(ptr1 || ptr2 || ptr3 || ptr4 || ptr5 || ptr6 || ptr7 || ptr8);
}

void imagine_fish(char thing[])
{
    strcat(thing, "fish");
}