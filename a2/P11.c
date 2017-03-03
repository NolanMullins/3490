#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/timeb.h>

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

	//Timing stuff
	struct timeb start, end;
	int dif;

	ftime(&start);

	//brute force
	int inv=0;
	for (int i = 0; i < size-1; i++)
		for (int j = i+1; j < size; j++)
			if (arr[i] > arr[j])
				inv++;
	ftime(&end);
	dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
	printf("Brute Force: %dms\n", dif);
	printf("Brute force inv: %d\n", inv);
	
    //free(arrtmp);
	free(arr);
	return 0;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	q1("data_1.txt");
	return 0;
}