#include "a2.h"

void visualize(char *code)
{
    for (int i = 0; i < 256; i++)
    {
        if (code[i] == '1')
        {
            printf(" ■ ");
        }
        else if (code[i] == '0')
        {
            printf("   ");
        }
        else
        {
            printf("___");
        }

        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
}

int main()
{
    // Task 1
    printf("%d\n", bitwise_xor(67));
    char *bin_string = xor_encrypt('C');
    printf("%c\n", xor_decrypt(bin_string));
    free(bin_string);

    // Task 2
    char *code = gen_code("Program in C!");
    char *msg = read_code(code);
    printf("%s\n", msg);
    free(msg);

    // Task 3
    char *hexcode = compress(code);
    printf("%s\n", hexcode);
    free(code);

    code = decompress(hexcode);
    free(hexcode);
    char *samehexcode = compress(code);
    printf("%s\n", samehexcode);
    free(code);
    free(samehexcode);

    // Task 4
    printf("%d\n", calc_ld("COMMENCE", "CODING"));
    printf("%d\n", calc_ld("COMMENCE", "PROCRASTINATING"));
    printf("%d\n", calc_ld("KITTEN", "SITTING"));
    printf("%d\n", calc_ld("HORSE", "ROS"));
    printf("%d\n", calc_ld("INTENTION", "EXECUTION"));

    return 0;
}