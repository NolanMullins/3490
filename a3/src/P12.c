#include <stdio.h>
#include <stdlib.h>
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

int cmpE(const void* a, const void* b)
{
	static int c = 0;
	c+=1;
	//printf("%s - %s\n", *(const char**)(a), *(const char**)(b));
	//if (c < 10)
		//printf("%s (%d) - %s (%d) = %d\n", *(const char**)(a), strToI(*(char**)(a)), *(const char**)(b), strToI(*(char**)(b)), strToI(*(char**)(a)) - strToI(*(char**)(b)));
	return (strToI(*(char**)(a)) - strToI(*(char**)(b)));
}

void bubble(void** arr, int size, int (*cmp)(const void *, const void*))
{
	int flag = 1;
	for (int a = 0; a < size-1; a++)
	{
		for (int b = a+1; b < size; b++)
		{
			if (cmp(&arr[a], &arr[b]) > 0)
			{
				flag = 0;
				void* tmp = arr[a];
				arr[a] = arr[b];
				arr[b] = tmp;
			}
		}
		if (flag)
			break;
	}
}

char** sortArr(char** arr, int size)
{
	for (int a = 0; a < size; a++)
		arr[a] = sortWord(arr[a]);

	for (int a = 0; a < 10; a++)
		printf("%s\n", arr[a]);

	printf("\nSorting - size: %d\n\n", size);
	//qsort(arr, sizeof(arr[0]), size, cmpE);
	bubble((void**)arr, size, cmpE);
	//printf("done\n");
	for (int a = 0; a < 10; a++)
		printf("%s\n", arr[a]);
	/*for (int a = 0; a < size-1; a++)
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
	}*/
	return arr;
}

int runP12(char* search, char** arr, int size)
{
	arr = sortArr(arr, size);
	//for (int a = 0; a < 10; a++)
		//printf("%s\n", arr[a]);
	return -1;
}