#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>

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
	//Timing stuff
    struct timeb start, end;
    int dif;
    ftime(&start);

  	/*//other time
  	struct timespec start, finish;
  	double elapsed;
  	clock_gettime(CLOCK_MONOTONIC, &start);*/

	int c = 0;
	for (int a = 0; a < size; a++)
	{
		char* current = arr[a];
		int sizeA = strlen(search), sizeB = strlen(current) ;
		if (sizeA == sizeB)
		{
			int tmp = cmp(search, sizeA, current, sizeB);
			c+= tmp;
			if (tmp)
				printf("%s\n", current);
		}
	}

	/*clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Brute force: %lfms\n", elapsed*1000);*/
	ftime(&end);
    dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    printf("Brute Force: %dms\n", dif);

	return c;
}