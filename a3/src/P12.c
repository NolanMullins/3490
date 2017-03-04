#include <stdio.h>
#include <string.h>

char* sortWord(char* word)
{
	int len = strlen(word);
	for (int a = 0; a < len-1; a++)
	{
		for (int b = a+1; b < len; b++)
		{
			if (word[a] > word[b])
			{
				char tmp = word[a];
				word[a] = word[b];
				word[b] = tmp;
			}
		}
	}
	return word;
}

int strToI(char* word)
{
	int num = 0;
	int len = strlen(word);
	for (int a = 0; a < len; a++)
		num = num*10 + word[a] - '0';
	return num;
}

char** sortArr(char** arr, int size)
{
	for (int a = 0; a < size-1; a++)
		arr[a] = sortWord(arr[a]);


	for (int a = 0; a < size-1; a++)
	{
		for (int b = a+1; b < size; b++)
		{
			if (strToI(arr[a]) > strToI(arr[b]))
			{
				char* tmp = arr[a];
				arr[a] = arr[b];
				arr[b] = tmp;
			}
		}
	}
	return arr;
}

int runP12(char* search, char** arr, int size)
{
	arr = sortArr(arr, size);
	for (int a = 0; a < 10; a++)
		printf("%s\n", arr[a]);
	return -1;
}