#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "P22.h"

void suffixTable(char* pattern, int* table, int size)
{
	int border[size+1];
	//*border = 0;
	for (int a = 0; a < size+1; a++)
		table[a] = 0;
    int a = size, b = size+1;
    border[a]=b;
    while (a > 0)
    {
        while (b <= size && pattern[a-1] != pattern[b-1])
        {
            if (table[b]==0)
            	table[b]=b-a;
            b=border[b];
        }
        a-=1; 
        b-=1;
        border[a] = b;
    }
    b = border[0];
    for(int c = 0; c <= size; c++)
    {
    	if (table[c] == 0)
    		table[c] = b;
    	if (c == b)
    		b = border[b];
    }
}

void runP23(char* file, char* search)
{

	FILE* f = fopen(file, "r");
	int i=0;
	char c;
	char string[3296592];
	while ((c = getc(f)) != EOF)
		string[i++] = c;
	string[i] = '\0';

	int size = strlen(search);
	int shiftTable[52] = {[0 ... 51] = -1};
	for (int a = 0; a < size; a++)
		shiftTable[asciiToIndex(search[a])]=a;

	//for (int a = 0; a < 52; a++)
		//printf("%d : %d\n", a, shiftTable[a]);

	int suffix[size+1];
	suffix[size] = 0;
	suffixTable(search, suffix, size);

	//Timing stuff
    /*struct timeb start, end;
    int dif;
    ftime(&start);*/

  	//other time
  	struct timespec start, finish;
  	double elapsed;
  	clock_gettime(CLOCK_MONOTONIC, &start);

	i=0;
    int j,found=0, tmpShifts=0;
    while (i<=3296592-size)
    {
    	tmpShifts++;
        j=size-1;
        while (j>=0 && search[j]==string[i+j]) 
        	j--;
        if (j<0)
        {
            found++;
           // for (int a = i; a < i+size; a++)
            	//printf("%c", string[a]);
            //printf("\n");
            i+=suffix[0];
        }
        else 
        {
        	int charShift = 0;
        	//check if current char is in bounds of the shift table
        	if (isChar(string[i+j]))
        		charShift = shiftTable[asciiToIndex(string[i+j])];
        	else 
        		charShift = -1;
        	//calc offset
        	int shift = j-charShift;
        	//check for bigger offset by suffix
        	if (suffix[j+1] > shift)
        		shift = suffix[j+1];
        	i+=shift;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	
	/*ftime(&end);
    dif = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    printf("Brute Force: %dms\n", dif);*/

    printf("Boyer-Moore:\tfound: %d shifts: %d\n", found, tmpShifts);
    printf("Time: %lfms\n", elapsed*1000);
}