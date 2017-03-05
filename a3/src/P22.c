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

void runP22(char* file)
{

	FILE* f = fopen(file, "r");
	int i =0;
	char c;
	char string[3296592];
	while ((c = getc(f)) != EOF)
		string[i++] = c;
	string[i] = '\0';

	char search[32];
	printf("Show  me what you got: \n");
	fgets(search, 32, stdin);

	int size = strlen(search);
	if (search[size-1] == '\n')
		search [--size] = '\0';

	int shiftTable[52] = {[0 ... 51] = size};

	for (int a = 0; a < size; a++)
	{
		shiftTable[asciiToIndex(search[a])] = rightMost(search, search[a]);
	}

	
	for (int a = 0; a < 52; a++)
	{
		int index = a+65;
		if (index > 90)
			index += 6;
		printf("%c - %d\n", (char)(index), shiftTable[asciiToIndex((char)index)]);
	}

}