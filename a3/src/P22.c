#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int rightMost(char* string, char look)
{
	for (int a = strlen(string)-1; a >= 0; a--)
		if (string[a] == look)
			return strlen(string) - a - 1;
	return strlen(string);
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

int asciiToIndex(char ascii)
{
	if (!isChar(ascii))
		return 52;
	int charToIndex = (int)ascii;
	if (charToIndex > 90)
		charToIndex -= 6;
	charToIndex-=65;
	return charToIndex;
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

	for (int a = 0; a < size-1; a++)
		shiftTable[asciiToIndex(search[a])] = size-1-a;

	int index = size-1;
	int count = 0;
	int shifts = 0;

	//Timing stuff
    /*struct timeb start, end;
    int dif;
    ftime(&start);*/

  	//other time
  	struct timespec start, finish;
  	double elapsed;
  	clock_gettime(CLOCK_MONOTONIC, &start);

	while (index < 3296592)
	{
		shifts += 1;
		//printf("Test %d\n", index);
		if (!isChar(string[index]))
		{
			index+=size;
			continue;
		}
		// /printf("%d\n", index);
		int shift = shiftTable[asciiToIndex(string[index])];
		int flag = 1;
		for (int a = 0; a < size; a++)
			if (string[index-a] != search[size-1-a])
			{
				flag = 0;
				break;
			}

		if (flag)
			count++;
		if (shift == 0)
			shift = size;
		index+=shift;
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	
	/*ftime(&end);
    dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    printf("Brute Force: %dms\n", dif);*/

	printf("Horsepool:\tfound: %d shifts: %d\n", count, shifts);
	printf("Time: %lfms\n", elapsed*1000);
}