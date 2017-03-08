#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rightMost(char* string, char look)
{
	for (int a = strlen(string)-1; a >= 0; a--)
		if (string[a] == look)
			return strlen(string) - a - 1;
	return strlen(string);
}

int asciiToIndex(char ascii)
{
	int charToIndex = (int)ascii;
	if (charToIndex > 90)
		charToIndex -= 6;
	charToIndex-=65;
	return charToIndex;
}

int isChar(char test)
{
	int val = (int)test;
	if (val >= 65 && val <= 90)
		return 1;
	if (val >= 97 && val <= 122)
		return 1;
	return 0;
}

int nextOcc(char* string, char look, int curIndex)
{
	for (int a = curIndex-1; a >= 0; a--)
		if (string[a] == look)
			return strlen(string) - a - 1;
	return strlen(string);
}

void runP22(char* file, char* search)
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