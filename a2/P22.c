#include <stdio.h>
#include <stdlib.h>

void loadArr(char* file, double** arr, int* size)
{
	FILE* f = fopen(file, "r");
	if (f == NULL)
		printf("File not found\n");
	//char string[256];
	int c = 0;
	while (fscanf(f, "%lf", &arr[(int)(c/2)][c%2]) > 0)c++;
	fclose(f);
	*size = c/2;
}

typedef struct data
{
	int id;
	double** arr;
	int size;
	int* threadsIsUse;
	int maxThreads;
} Data;

void merge(double** a, int sa, double** b, int sb, double** main)
{
	int  i=0, j=0, k=0;
	//loop through a pick the smallest numbers from the partioned arrays and put them in the main one
	while (i < sa && j < sb)
	{
		if (a[i][0] < b[j][0])
			main[k] = a[i++];
		else
			main[k] = b[j++];
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

void cpyData(Data* data, Data* newData, double** arr, int size)
{
	newData->id = data->id;
	newData->arr = arr;
	newData->size = size;
	newData->threadsIsUse = data->threadsIsUse;
	newData->maxThreads = data->maxThreads;
}

void* mergeSort(void* param)
{
	Data* data = (Data*)param;
	if (data->size <= 1)
		return NULL;

	double** arr = data->arr;
	int size = data->size;
	
	int sa = size/2;
	int sb = size - (int)(size/2);
	double** arrA = malloc(sizeof(double*)*sa);
	double** arrB = malloc(sizeof(double*)*sb);
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
	//merge data
	merge(arrA, sa, arrB, sb, arr);
	free(arrA);
	free(arrB);
	return NULL;
}

void addPoint(double** pts, double* newpt, int* len)
{
	for (int a = 0; a < *len; a++)
		if (pts[a][0] == newpt[0] && pts[a][1] == newpt[1])
			return;
	pts[*len][0] = newpt[0];
	pts[*len][1] = newpt[1];
	(*len)++;
}

float qsqrt(float n)
{
	long i;
	float x2, y;
	x2 = n*.5;
	y = n;
	i = *(long*)&y;
	i  = 0x5f3759df - ( i >> 1 );
	y = *(float*)&i;
	y = y*(1.5f-(x2*y*y));
	return y;
}

double dist(double* A, double* B, double* pt)
{
	double y2My1 = B[1] - A[1];
	double x2Mx1 = B[0] - A[0];
	float sq = y2My1*y2My1 + x2Mx1*x2Mx1;
	return (y2My1*pt[0] - x2Mx1*pt[1] + B[0]*A[1] - B[1]*A[0])/(1/qsqrt(sq));
}

void findHull(double** arr, int size, double* A, double* B, double** pts, int* nPts)
{
	if (size < 1)
		return;

	double distMax =0;
	int index = 0;
	for (int a = 0; a < size; a++)
	{
		double d = dist(A, B, arr[a]);
		if (d > distMax)
			index = a;
	}
	addPoint(pts, arr[index], nPts);

	double** arr1 = malloc(sizeof(double*)*size);
	printf("Test\n");
	double** arr2 = NULL;
	printf("Test2\n");
	malloc(10000*sizeof(int*));
	printf("Test3\n");
	int c1 = 0, c2 = 0;

	double* C = arr[index];

	//partition shit
	for (int a = 1; a < size - 2; a++)
	{
		if (a==index)
			continue;
		double* D = arr[a];
		//A to C to D
		float v1 = (C[0] - A[0])*(D[1] - A[1]) - (D[0] - A[0])*(C[1] - A[1]);
		//C to B to D
		float v2 = (B[0] - C[0])*(D[1] - C[1]) - (D[0] - C[0])*(B[0] - C[1]);
		if (v1 > 0)
			arr1[c1++] = arr[a];
		else if (v2 > 0)
			arr2[c2++] = arr[a];
	}

	findHull(arr1, c1-1, A, C, pts, nPts);
	findHull(arr2, c2-1, C, B, pts, nPts);

	free(arr1);
	free(arr2);
}

void divHull(double** arr, int size, double** pts, int* nPts)
{
	double* A = arr[0];
	double* B = arr[size-1];
	addPoint(pts, A, nPts);
	addPoint(pts, B, nPts);

	double** arr1 = malloc(sizeof(double*)*size);
	double** arr2 = malloc(sizeof(double*)*size);
	int c1 = 0, c2 = 0;

	double x1 = A[0], y1 = A[1], x2 = B[0], y2 = B[0];
	for (int a = 1; a < size - 2; a++)
	{
		double x3 = arr[a][0], y3 = arr[a][1];
		float value = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
		if (value > 0)
			arr1[c1++] = arr[a];
		else
			arr2[c2++] = arr[a];
	}
	findHull(arr1, size1, A, B, pts, nPts);
	findHull(arr2, size2, B, A, pts, nPts);

	free(arr1);
	free(arr2);
}

int main(int argc, char* argv[])
{
	//load points into an arrya
	double** arr = malloc(sizeof(double*)*50000);
	for (int a = 0; a < 50000; a++)
		arr[a] = malloc(sizeof(double)*2);
	double** pts = malloc(sizeof(double*)*500);
	for (int a = 0; a < 500; a++)
		pts[a] = malloc(sizeof(double)*2);
	int numPts = 0;

	int size = 0;
	loadArr("data/q2", (double**)arr, &size);
	Data d;
	d.id = 0;
	d.arr = arr;
	d.size = size;
	d.maxThreads = -1;
	printf("Loaded\n");
	mergeSort(&d);

	divHull(arr, size, pts, &numPts);

	printf("Points\n");
	for (int a = 0; a < numPts; a++)
		printf("%lf %lf\n", pts[a][0], pts[a][1]);
	//free memory
	for (int a = 0; a < 50000; a++)
		free(arr[a]);
	free(arr);
}