#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "P11.h"

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

void bubble(void** arr, void** arrCpy, int size, int (*cmp)(const void *, const void*))
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
				tmp = arrCpy[a];
				arrCpy[a] = arrCpy[b];
				arrCpy[b] = tmp;
			}
		}
		if (flag)
			break;
	}
}

char** sortArr(char** arr, char** arrCpy, int size)
{
	for (int a = 0; a < size; a++)
		arr[a] = sortWord(arr[a]);

	/*for (int a = 0; a < 10; a++)
		printf("%s\n", arr[a]);*/

	//printf("\nSorting - size: %d\n\n", size);
	printf("Im sorry, my merge sort isnt set up for generic data and the threading will break valgrind :(\n...\n");
	//qsort wasnt working, not really sure why
	//qsort(arr, sizeof(arr[0]), size, cmpE);
	bubble((void**)arr, (void**)arrCpy, size, cmpE);
	printf("Well that happened\n");
	//printf("done\n");
	/*for (int a = 0; a < 10; a++)
		printf("%s\n", arr[a]);*/
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

int runP12(char* search, char** arr, char** arrCpy, int size)
{
	arr = sortArr(arr, arrCpy,size);

	//Timing stuff
    /*struct timeb start, end;
    int dif;
    ftime(&start);*/

  	//other time
  	struct timespec start, finish;
  	double elapsed;
  	clock_gettime(CLOCK_MONOTONIC, &start);

	int c = 0;
	int flag = 0;
	for (int a = 0; a < size; a++)
	{
		char* current = arr[a];
		int sizeA = strlen(search), sizeB = strlen(current) ;
		if (sizeA == sizeB)
		{
			int tmp = cmp(search, sizeA, current, sizeB);
			c+= tmp;
			if (tmp)
			{
				printf("%s\n", arrCpy[a]);
				flag = 1;
			}
			else if (flag)
				break;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Pre Sort: %lfms\n", elapsed*1000);
	/*ftime(&end);
    dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    printf("Brute Force: %dms\n", dif);*/

	//for (int a = 0; a < 10; a++)
		//printf("%s\n", arr[a]);
	return c;
}