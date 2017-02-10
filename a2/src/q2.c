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

int main(int argc, char* argv[])
{
	//load points into an arrya
	double** arr = malloc(sizeof(double*)*50000);
	for (int a = 0; a < 50000; a++)
		arr[a] = malloc(sizeof(double)*2);
	int size = 0;
	loadArr("data/tmp", (double**)arr, &size);
	printf("Loaded\n");
	/*for (int a = 0; a < size; a++)
		printf("%lf %lf\n", arr[a][0], arr[a][1]);*/

	for (int a = 0; a < size; a++)
	{
		for (int b = a+1; b < size; b++)
		{
			//generate line bwetween point a b
			double x1 = arr[a][0],y1 = arr[a][1];
			double x2 = arr[b][0],y2 = arr[b][1];
			//m = y2-y1 / x2-x1
			//float m = (y2 - y1) / (x2 - x1);

			//loop through other points
			int flag = 0;
			for (int c = 0; c < size; c++)
			{
				if (c == a || c == b)
					continue;
				double x3 = arr[c][0],y3 = arr[c][1];
				float value = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
				/*if ((x1 == 3.2 || x2 == 3.2) &&  (y1 == 3 || y2 == 3))
					printf("f: %d, v: %.3f\n", flag, value);*/
				//if p3 is on the right of the line
				if (value < 0)
				{
					if (flag < 0)
					{
						flag = 0;
						break;
					}
					flag = 1;
				}
				else if (value > 0)
				{
					if (flag > 0)
					{
						flag = 0;
						break;
					}
					flag = -1;
				}
			}
			if (flag != 0)
			{
				printf("Point:\n");
				printf("%lf %lf\n", arr[a][0], arr[a][1]);
				printf("%lf %lf\n", arr[b][0], arr[b][1]);
			}
		}
	}


	//free memory
	for (int a = 0; a < 50000; a++)
		free(arr[a]);
	free(arr);
}