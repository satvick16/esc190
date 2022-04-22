#include <stdio.h>
#include <math.h>

char bin_to_hex(char *four_bin)
{
    // takes a four digit array of binary and returns one character of hex
    // first convert the char to an int
    int bin = 0;
    double times = 3;
    for (int i = 0; i < 4; i++)
    {
        bin += (four_bin[i] - '0') * pow(10.0, times);
        times--;
    }

    int hexConstant[] = {0, 1, 10, 11, 100, 101, 110, 111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111};
    char corresponding[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    for (int i = 0; i < 16; i++)
    {
        if (bin == hexConstant[i])
        {
            return corresponding[i];
        }
    }
}

int main()
{
    char *f = "1000";
    printf("%c\n", bin_to_hex(f));

    return 0;
}