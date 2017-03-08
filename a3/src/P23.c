#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "P22.h"

void runP23(char* file, char* search)
{

	FILE* f = fopen(file, "r");
	int i =0;
	char c;
	char string[3296592];
	while ((c = getc(f)) != EOF)
		string[i++] = c;
	string[i] = '\0';

	int size = strlen(search);
	int shiftTable[52] = {[0 ... 51] = size};

	for (int a = 0; a < size; a++)
	{
		shiftTable[asciiToIndex(search[a])] = rightMost(search, search[a]);
	}

	
	/*for (int a = 0; a < 52; a++)
	{
		int index = a+65;
		if (index > 90)
			index += 6;
		printf("%c - %d\n", (char)(index), shiftTable[asciiToIndex((char)index)]);
	}*/
	int index = size-1;
	int count = 0;
	int shifts = 0;
	while (index < 3296592)
	{
		shifts += 1;
		if (isChar(string[index]))
		{
			int shift = shiftTable[asciiToIndex(string[index])];
			if (shift == 0)
			{
				int flag = 1;
				for (int b = 0; b < size; b++)
				{
					//printf("%c = %c",index-size+1+b, search[b]);
					if (string[index-size+1+b] != search[b])
					{
						flag = 0;
						break;
					}
				}
				if (flag)
					count++;
				index+=size;
			}
			else
				index += shift;
		}
		else
			index+=size;
	}

	printf("%d - %d\n", count, shifts);

}