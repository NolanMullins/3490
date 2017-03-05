#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <string.h>
#include <time.h>

void runP21(char* file)
{

	FILE* f = fopen(file, "r");
	int i =0;
	char c;
	char string[3296592];
	while ((c = getc(f)) != EOF)
		string[i++] = c;
	string[i] = '\0';

	char search[32];
	printf("Show  me what you got: \n");
	fgets(search, 32, stdin);

	int size = strlen(search);
	if (search[size-1] == '\n')
		search [--size] = '\0';

	//Timing stuff
    /*struct timeb start, end;
    int dif;
    ftime(&start);*/

  	//other time
  	struct timespec start, finish;
  	double elapsed;
  	clock_gettime(CLOCK_MONOTONIC, &start);

	int count = 0;
	int switches = 0;
	for (int a = 0; a < 3296591 - size; a++)
	{
		switches++;
		if (string[a] == search[0])
		{
			int flag = 1;
			for (int b = 0; b < size; b++)
			{
				if (string[a+b] != search[b])
				{
					flag = 0;
					break;
				}
			}
			if (flag)
				count++;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("%lfms\n", elapsed*1000);
	/*ftime(&end);
    dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    printf("Brute Force: %dms\n", dif);*/

	printf("Found %d matches, %d switches\n", count, switches);
}