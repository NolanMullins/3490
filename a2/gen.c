#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[])
{
	if (argc < 3)
		exit(0);
	srand(time(NULL));
	FILE* f = fopen("data/tmp2", "w");
	for (int a = 0; a < atoi(argv[1]); a++)
		fprintf(f, "%d %d\n", rand()%atoi(argv[2]), rand()%atoi(argv[2]));
	fclose(f);
}