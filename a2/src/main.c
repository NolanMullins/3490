#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

int* loadArr(char* file, int* size)
{
	FILE* f = fopen(file, "r");
	//char string[256];
	int *arr = malloc(sizeof(int)*50000);
	int c = 0;
	while (fscanf(f, "%d", &arr[c++]) > 0);
	fclose(f);
	*size = c-1;
	return arr;
}

int q1 (char* file)
{
	int size;
	int* arr = loadArr(file, &size);

	//brute force
	int data=0;
	for (int i = 0; i < size-1; i++)
		for (int j = i+1; j < size; j++)
			if (arr[i] > arr[j])
				data++;


	free(arr);
	return data;
}

int main(int argc, char* argv[])
{
	printf("inv %d\n", q1("data/q1"));

	return 0;
}