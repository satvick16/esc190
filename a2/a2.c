#include "a2.h"

int bitwise_xor(int value)
{
	// finished
	return KEY ^ value;
}

char *xor_encrypt(char c)
{
	// finished
	char *res = (char *)malloc(8 * (sizeof(char)));
	int val = bitwise_xor(c);

	for (int i = 6; i >= 0; i--)
	{
		if (val >= pow(2, i))
		{
			res[6 - i] = '1';
			val -= pow(2, i);
		}
		else
		{
			res[6 - i] = '0';
		}
	}

	res[7] = '\0';

	return res;
}

char xor_decrypt(char *s)
{
	// finished
	int binary = 0;

	for (int i = 0; i < 7; i++)
	{
		if (s[i] == '1')
		{
			binary += pow(2, 6 - i);
		}
	}

	int val = bitwise_xor(binary);

	return (char)val;
}

char *gen_code(char *msg)
{
	// finished
	char *res = (char *)calloc(257, sizeof(char));

	int pain[52] = {0, 1, 2, 3, 4, 11, 12, 13, 14, 15, 16, 20, 27, 31, 32, 34, 36, 43, 45, 47, 48, 52, 59, 63, 64, 65, 66, 67, 68, 75, 76, 77, 78, 79, 176, 177, 178, 179, 180, 192, 196, 208, 210, 212, 224, 228, 240, 241, 242, 243, 244, 255};
	int agony[24] = {17, 18, 19, 28, 29, 30, 33, 35, 44, 46, 49, 50, 51, 60, 61, 62, 193, 194, 195, 209, 211, 225, 226, 227};

	for (int i = 0; i < 52; i++)
	{
		res[pain[i]] = '1';
	}

	for (int i = 0; i < 24; i++)
	{
		res[agony[i]] = '0';
	}

	if (msg[0] == '\0')
	{
		char *encrypted = (char *)malloc(8);
		char *temp2 = xor_encrypt('\0');
		strcat(encrypted, temp2);
		free(temp2);

		// copy into res
		int blanks[256 - 76];

		int tracker = 0;

		for (int i = 0; i < 256; i++)
		{
			if (res[i] != '0' && res[i] != '1')
			{
				blanks[tracker] = i;
				tracker++;
			}
		}

		for (int i = 0; i < 7; i++)
		{
			res[blanks[i]] = encrypted[i];
		}

		for (int i = 0; i < 256; i++)
		{
			if (res[i] != '0' && res[i] != '1')
			{
				res[i] = '0';
			}
		}

		free(encrypted);

		return res;
	}
	else
	{
		// encrypt string
		char *encrypted = (char *)malloc(8);
		int size = 8;

		char *temp = xor_encrypt(msg[0]);
		strcpy(encrypted, temp);
		free(temp);

		int iterator = 1;

		while (msg[iterator] != '\0')
		{
			size += 7;
			encrypted = realloc(encrypted, size);
			char *temp = xor_encrypt(msg[iterator]);
			strcat(encrypted, temp);
			free(temp);

			iterator++;
		}

		size += 7;
		encrypted = realloc(encrypted, size);
		char *temp2 = xor_encrypt('\0');
		strcat(encrypted, temp2);
		free(temp2);

		// copy into res
		int blanks[256 - 76];

		int tracker = 0;

		for (int i = 0; i < 256; i++)
		{
			if (res[i] != '0' && res[i] != '1')
			{
				blanks[tracker] = i;
				tracker++;
			}
		}

		for (int i = 0; i < size; i++)
		{
			res[blanks[i]] = encrypted[i];
		}

		for (int i = 0; i < 256; i++)
		{
			if (res[i] != '0' && res[i] != '1')
			{
				res[i] = '0';
			}
		}

		free(encrypted);

		return res;
	}
}

char *read_code(char *code)
{
	// finished

	// fill in template
	int pain[52] = {0, 1, 2, 3, 4, 11, 12, 13, 14, 15, 16, 20, 27, 31, 32, 34, 36, 43, 45, 47, 48, 52, 59, 63, 64, 65, 66, 67, 68, 75, 76, 77, 78, 79, 176, 177, 178, 179, 180, 192, 196, 208, 210, 212, 224, 228, 240, 241, 242, 243, 244, 255};
	int agony[24] = {17, 18, 19, 28, 29, 30, 33, 35, 44, 46, 49, 50, 51, 60, 61, 62, 193, 194, 195, 209, 211, 225, 226, 227};

	char *temp = (char *)calloc(257, 1);

	for (int i = 0; i < 52; i++)
	{
		temp[pain[i]] = '1';
	}

	for (int i = 0; i < 24; i++)
	{
		temp[agony[i]] = '0';
	}

	int blanks[256 - 76];

	int marker = 0;

	for (int i = 0; i < 256; i++)
	{
		if (temp[i] != '1' && temp[i] != '0')
		{
			blanks[marker] = i;
			marker++;
		}
	}

	free(temp);

	// encrypted message
	char msg[256 - 76];

	for (int i = 0; i < 256 - 76; i++)
	{
		msg[i] = code[blanks[i]];
	}

	// decrypt
	char *decrypted = (char *)calloc(257, 1);

	int i = 0;

	while (i <= 168)
	{
		char throwaway[7];
		strncpy(throwaway, &msg[i], 7);
		char s = xor_decrypt(throwaway);
		strncat(decrypted, &s, 1);
		i += 7;
	}

	// SSSSSSSSSSSSSSSSSSSSSSS
	// Program in C!SSSSSSSSSSS

	// remove trailing, vestigial characters
	int last = -1;

	for (int i = 23; i >= 0; i--)
	{
		if (decrypted[i] != KEY)
		{
			last = i;
			break;
		}
	}

	char *final = (char *)calloc(last + 2, 1);
	strncpy(final, &decrypted[0], last + 1);

	free(decrypted);

	return final;
}

// char *compress(char *code)
// {
// 	char *res = (char *)calloc(65, sizeof(char));

// 	char *temp = (char *)malloc(4 * sizeof(char));

// 	int count = 0;

// 	long decimalnum, quotient, remainder;
// 	char hexadecimalnum;

// 	for (int i = 0; i < 256; i++)
// 	{
// 		if (count == 3)
// 		{
// 			temp[count] = code[i];
// 			decimalnum = (temp[0] - '0') * 8 + (temp[1] - '0') * 4 + (temp[2] - '0') * 2 + (temp[3] - '0');

// 			if (decimalnum < 10)
// 			{
// 				res[i / 4] = decimalnum + '0';
// 			}
// 			else
// 			{
// 				if (decimalnum == 10)
// 				{
// 					res[i / 4] = 'A';
// 				}
// 				else if (decimalnum == 11)
// 				{
// 					res[i / 4] = 'B';
// 				}
// 				else if (decimalnum == 12)
// 				{
// 					res[i / 4] = 'C';
// 				}
// 				else if (decimalnum == 13)
// 				{
// 					res[i / 4] = 'D';
// 				}
// 				else if (decimalnum == 14)
// 				{
// 					res[i / 4] = 'E';
// 				}
// 				else if (decimalnum == 15)
// 				{
// 					res[i / 4] = 'F';
// 				}
// 			}

// 			count = 0;
// 		}
// 		else if (count < 4)
// 		{
// 			temp[count] = code[i];
// 			count++;
// 		}
// 	}

// 	free(temp);
// 	return res;
// }

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

char *compress(char *code)
{
	// first take the code and put it to number array
	char *final = calloc(65, sizeof(char));
	for (int i = 0; i < 64; i++)
	{
		char curr[5];
		for (int z = 0; z < 4; z++)
		{
			// printf("%d maybe this is the problem %c \n",i*4+z, code[i*4+z]);
			curr[z] = code[i * 4 + z];
		}
		final[i] = bin_to_hex(curr);
		// printf("%d this is final each round %c", i, final[i]);
	}

	final[64] = '\0';
	return final;
}

char *decompress(char *code)
{
	char *res = (char *)calloc(257, sizeof(char));
	int loc = 0;

	for (int i = 0; i < 64; i++)
	{
		char c = code[i];

		int num_val;

		if (c == '0')
		{
			num_val = 0;
		}
		if (c == '1')
		{
			num_val = 1;
		}
		if (c == '2')
		{
			num_val = 2;
		}
		if (c == '3')
		{
			num_val = 3;
		}
		if (c == '4')
		{
			num_val = 4;
		}
		if (c == '5')
		{
			num_val = 5;
		}
		if (c == '6')
		{
			num_val = 6;
		}
		if (c == '7')
		{
			num_val = 7;
		}
		if (c == '8')
		{
			num_val = 8;
		}
		if (c == '9')
		{
			num_val = 9;
		}

		if (c == 'A')
		{
			num_val = 10;
		}
		if (c == 'B')
		{
			num_val = 11;
		}
		if (c == 'C')
		{
			num_val = 12;
		}
		if (c == 'D')
		{
			num_val = 13;
		}
		if (c == 'E')
		{
			num_val = 14;
		}
		if (c == 'F')
		{
			num_val = 15;
		}

		// convert num_val to binary
		int temp[4] = {0, 0, 0, 0};

		for (int j = 0; num_val > 0; j++)
		{
			temp[j] = num_val % 2;
			num_val = num_val / 2;
		}

		// reverse and format into temp string
		int binary[4];

		for (int k = 3; k >= 0; k--)
		{
			binary[3 - k] = temp[k];
		}

		// convert binary[] into char array
		char despair[4];

		for (int k = 0; k < 4; k++)
		{
			if (binary[k] == 1)
			{
				despair[k] = '1';
			}
			else
			{
				despair[k] = '0';
			}
		}

		// add despair[] to res
		strncpy(&res[loc], despair, 4);
		loc += 4;
	}

	return res;
}

int lev(char *sandy, int s, char *cima, int c)
{
	// helper function for calc_ld
	int x, y, z;

	if (!s)
		return c;

	if (!c)
		return s;

	if (sandy[s - 1] == cima[c - 1])
		return lev(sandy, s - 1, cima, c - 1);

	x = lev(sandy, s - 1, cima, c - 1);
	y = lev(sandy, s, cima, c - 1);
	z = lev(sandy, s - 1, cima, c);

	if (x > y)
		x = y;
	if (x > z)
		x = z;

	return x + 1;
}

int calc_ld(char *sandy, char *cima)
{
	// finished
	int s, c;

	for (s = 0; sandy[s] != '\0'; s++)
		;
	for (c = 0; cima[c] != '\0'; c++)
		;

	return lev(sandy, s, cima, c);
}