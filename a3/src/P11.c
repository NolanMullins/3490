#include <stdio.h>
#include <string.h>

int cmp(char* wordA, int sizeA, char* wordB, int sizeB)
{
	int mapA[10] = {0};
	int mapB[10] = {0};
	for (int a = 0; a < sizeA; a++)
		mapA[wordA[a]-'0']++;
	for (int b = 0; b < sizeB; b++)
		mapB[wordB[b]-'0']++;
	for (int c = 0; c < 10; c++)
		if (mapA[c] != mapB[c])
			return 0;
	return 1;
}

int runP11(char* search, char** arr, int size)
{
	int c = 0;
	for (int a = 0; a < size; a++)
	{
		char* current = arr[a];
		int sizeA = strlen(search), sizeB = strlen(current) ;

		if (sizeA == sizeB)
			if (cmp(search, sizeA, current, sizeB))
				printf("a: %d c: %d, string: %s\n", a,++c, current);
			//c+=cmp(search, a, current, b);
	}
	return c;
}