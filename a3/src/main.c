#include <stdio.h>

#include "list.h"
#include "P11.h"
#include "P12.h"
#include "P21.h"
#include "P22.h"
#include "P23.h"

char** loadArr(char* file, int* size)
{
    FILE* f = fopen(file, "r");
    //char string[256];
    char **arr = malloc(sizeof(char*)*30000);
    for (int a = 0; a < 30000; a++)
    	arr[a] = malloc(sizeof(char)*32);
    int c = 0;
    while (fscanf(f, "%s", arr[c++]) > 0);
    fclose(f);
    *size = c-1;
    return arr;
}

void freeArr(char** arr, int size)
{
	for (int a = 0; a < size; a++)
        free(arr[a]);
    free(arr);
}

int main(int argc, char* argv[])
{
	int size = 0;
	char** arr = loadArr("data/data_4.txt", &size);
	//FILE* f = fopen("data/data_4.txt", "r");
	printf("1804289383 has %d matches\n", runP11("1804289383", arr, size));

	freeArr(arr, 30000);

	return 0;
}