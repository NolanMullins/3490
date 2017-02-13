#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

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
		else if (a[i][0] > b[j][0])
			main[k] = b[j++];
		else
		{
			if (a[i][1] < b[j][1])
				main[k] = a[i++];
			else
				main[k] = b[j++];
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

double dist4(double* A, double* B, double* C)
{

	return ((B[0] - A[0]) * (A[1] - C[1])) - ((B[1] - A[1]) * (A[0] - C[0]));
}

void findHull(double** arr, int size, double* A, double* B, double** pts, int* nPts)
{
	if (size < 1)
		return;
	double distMax =0;
	int index = 0;
	
	/*printf("\n");
	printf("A %lf, %lf\n", A[0], A[1]);
	printf("B %lf, %lf\n", B[0], B[1]);*/

	/*printf("Array\n");
	for (int a = 0; a < size; a++)
		printf("%lf, %lf\n", arr[a][0], arr[a][1]);
	printf("\n");*/

	//look for furthest point from the line
	for (int a = 0; a < size; a++)
	{
		double d = dist4(A, B, arr[a]);
		//printf("looking at: %lf, %lf, dist: %lf, dist4: %lf\n", arr[a][0], arr[a][1], d, dist4(A,B,arr[a]));
		if (d > distMax)
		{
			distMax = d;
			index = a;
		}
	}
	//add the furthest point
	addPoint(pts, arr[index], nPts);
	double** arr1 = malloc(sizeof(double*)*size);
	double** arr2 = malloc(sizeof(double*)*size);
	int c1 = 0, c2 = 0;
	
	double* C = arr[index];

	
	/*printf("Found C, %lf %lf\n", C[0], C[1]);

	printf("%lf, %lf to %lf, %lf\n", A[0], A[1], C[0], C[1]);
	printf("%lf, %lf to %lf, %lf\n", C[0], C[1], B[0], B[1]);*/
	//partition shit
	for (int a = 0; a < size; a++)
	{
		if (a==index)
			continue;
		double* D = arr[a];
		//A to C to D
		double v1 = (C[0] - A[0])*(D[1] - A[1]) - (D[0] - A[0])*(C[1] - A[1]);
		//C to B to D
		//double value = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1); C=X1 B=X2 D=X3
		float v2 = (B[0]-C[0])*(D[1] - C[1]) - (D[0] - C[0])*(B[1] - C[1]);
		//printf("looking at: %lf, %lf, v1: %lf, v2: %lf\n", arr[a][0], arr[a][1], v1, v2);
		if (v1 < 0)
			arr1[c1++] = arr[a];
		else if (v2 < 0)
			arr2[c2++] = arr[a];
	}
	
	findHull(arr1, c1, A, C, pts, nPts);
	findHull(arr2, c2, C, B, pts, nPts);
	
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

	double x1 = A[0], y1 = A[1], x2 = B[0], y2 = B[1];
	//split the arrays into to sections based on position to the line
	for (int a = 1; a < size - 1; a++)
	{
		double x3 = arr[a][0], y3 = arr[a][1];
		double value = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
		//left else right
		if (value < 0)
			arr1[c1++] = arr[a];
		else
			arr2[c2++] = arr[a];
	}

	/*printf("Right arr top\n");
	for (int a = 0; a < c2; a++)
		printf("%lf, %lf\n", arr2[a][0], arr2[a][1]);
	printf("\n");*/

	findHull(arr1, c1, A, B, pts, nPts);
	findHull(arr2, c2, B, A, pts, nPts);

	free(arr1);
	free(arr2);
}

int main(int argc, char* argv[])
{
	//load points into an arrya
	double** arr = malloc(sizeof(double*)*50000);
	for (int a = 0; a < 50000; a++)
		arr[a] = malloc(sizeof(double)*2);
	int ptsSize = 100;
	double** pts = malloc(sizeof(double*)*ptsSize);
	for (int a = 0; a < ptsSize; a++)
		pts[a] = malloc(sizeof(double)*2);
	int numPts = 0;
	int size = 0;

	/*srand(time(NULL));
	for (int a = 0; a < 50; a++)
		printf("%d %d\n", rand()%30, rand()%30);*/


	loadArr("data/q2", (double**)arr, &size);
	Data d;
	d.id = 0;
	d.arr = arr;
	d.size = size;
	d.maxThreads = -1;
	mergeSort(&d);

	//Timing stuff
	struct timeb start, end;
	int dif;

	ftime(&start);
	divHull(arr, size, pts, &numPts);
	ftime(&end);
	dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
	

	printf("Points: %d\n", numPts);
	for (int a = 0; a < numPts; a++)
		printf("%lf %lf\n", pts[a][0], pts[a][1]);

	printf("Div + conq: %dms\n", dif);
	//free memory
	for (int a = 0; a < 50000; a++)
		free(arr[a]);
	free(arr);
	for (int a = 0; a < ptsSize; a++)
		free(pts[a]);
	free(pts);
}