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

void merge(int* a, int sa, int* b, int sb, int* main)
{
	int  i=0, j=0, k=0;
	while (i < sa && j < sb)
	{
		if (a[i] < b[j])
			main[k] = a[i++];
		else
			main[k] = b[j++];
		k++;
	}
	if (i == sa)
		while (j < sb)
			main[k++] = b[j++];
	else
		while (i < sa)
			main[k++] = a[i++];
}

void* mergeSort(int* arr, int size)
{
	if (size <= 1)
		return NULL;
	int sa = size/2;
	int sb = size - (int)(size/2);
	int arrA[sa];
	int arrB[sb];
	int a;
	for (a = 0; a < sa; a++)
		arrA[a] = arr[a];
	for (int b = 0; b < sb; b++)
		arrB[b] = arr[a++];

	//sort
	mergeSort(arrA, sa);
	mergeSort(arrB, sb);
	//merge
	merge(arrA, sa, arrB, sb, arr);

	return NULL;
}

int q1 (char* file)
{
	int size;
	int* arr = loadArr(file, &size);

	//brute force
	/*int data=0;
	for (int i = 0; i < size-1; i++)
		for (int j = i+1; j < size; j++)
			if (arr[i] > arr[j])
				data++;*/
	int arrtmp[] = {4,2,7,1,0};

	mergeSort(arrtmp, 5);
	for (int a = 0; a < 5; a++)
		printf("%d\n", arrtmp[a]);

	free(arr);
	return 0;
}

int main(int argc, char* argv[])
{
	printf("inv %d\n", q1("data/q1"));

	return 0;
}