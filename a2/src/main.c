#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <pthread.h>
//#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>

typedef struct data
{
	int id;
	int* arr;
	int size;
	int* threadsIsUse;
	int maxThreads;
	int inversions;
} Data;

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

void merge(int* a, int sa, int* b, int sb, int* main, int* inversions)
{
	int  i=0, j=0, k=0;
	//loop through a pick the smallest numbers from the partioned arrays and put them in the main one
	while (i < sa && j < sb)
	{
		if (a[i] < b[j])
			main[k] = a[i++];
		else
		{
			main[k] = b[j++];
			(*inversions) += sa-i;
		}
		k++;
	}
	//put the remaining numbers in the main array
	if (i == sa)
		while (j < sb)
			main[k++] = b[j++];
	else
		while (i < sa)
			main[k++] = a[i++];
}

void cpyData(Data* data, Data* newData, int* arr, int size)
{
	newData->id = data->id;
	newData->arr = arr;
	newData->size = size;
	newData->threadsIsUse = data->threadsIsUse;
	newData->maxThreads = data->maxThreads;
	newData->inversions = 0;
}

void* mergeSort(void* param)
{
	Data* data = (Data*)param;
	if (data->size <= 1)
		return NULL;

	int* arr = data->arr;
	int size = data->size;
	
	int sa = size/2;
	int sb = size - (int)(size/2);
	int* arrA = malloc(sizeof(int)*sa);
	int* arrB = malloc(sizeof(int)*sb);
	int a;
	//copy data from main array into partions
	for (a = 0; a < sa; a++)
		arrA[a] = arr[a];
	for (int b = 0; b < sb; b++)
		arrB[b] = arr[a++];

	Data dataA, dataB;
	cpyData(data, &dataA, arrA, sa);
	cpyData(data, &dataB, arrB, sb);
	//sort
		/*int flag = 0;
		pthread_t thread;
		//attempt to create a new thread
		if (*(data->threadsIsUse) < (data->maxThreads-1))
		{
			*(data->threadsIsUse) += 1;
			dataA.id = *(data->threadsIsUse);
			//printf("Creating new Thread: %d\n", dataA.id);
			flag = 1;
			int sts = pthread_create(&thread, NULL, mergeSort, &dataA);
			if (sts)
			{
				printf("error creating thread, error code: %d\n", sts);
				flag = 0;
				mergeSort(&dataA);
			}
		}
		else
		{
			mergeSort(&dataA);
		}*/
	mergeSort(&dataA);
	mergeSort(&dataB);
		//merge
		/*if (flag)
			 pthread_join(thread,NULL);*/
	//count inversions
	data->inversions = dataA.inversions + dataB.inversions;
	//merge data
	merge(arrA, sa, arrB, sb, arr, &(data->inversions));
	free(arrA);
	free(arrB);
	return NULL;
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
	//tmp array for testing efficiency
	/*int tmpS = 50000000;
	int* arrtmp = malloc(sizeof(int)*tmpS);

	for (int a = 0; a<tmpS; a++)
		arrtmp[a] = rand()%(tmpS*1000) + 1;*/

	//threading
	int threadCount = 0;/*sysconf(_SC_NPROCESSORS_ONLN);
	printf("%d threads available\n", threadCount);*/
	int threadUse = 0;
	Data data;
	data.id = 0;
	//select array to be sorted
	data.arr = arr;
	data.size = size;
	data.threadsIsUse = &threadUse;
	data.maxThreads = threadCount;
	data.inversions = 0;

	
	ftime(&start);

	mergeSort(&data);

	ftime(&end);
	dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));

	printf("Div + conq: %dms\n", dif);
    printf("Div + conq inv: %d\n", (data.inversions));

    //free(arrtmp);
	free(arr);
	return 0;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	q1("data/q1");
	return 0;
}