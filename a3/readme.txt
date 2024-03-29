/****************************************
 * Nolan Mullins
 * 0939720
 * 12/03/2017
 * cis3490 - A3
 ****************************************/


**********************************
Problem
**********************************
    P1 - Search through a set of numbers and look for matching anagrams
    P2 - search through a set of characters looking for a key

**********************************
Algorithm
**********************************
	Brute force alogorithm for poth problems
	Presorted search for anagrams
	Horsepool and boyer-moore for searching keys

**********************************
Guide
**********************************
	Compile
	type: make
	output: run

	Running
	type: ./run
	
	

**********************************
Performance analysis
**********************************
	info = (found, shifts, time)

	Term				BruteForce info 		Horsepool info			Boyer-Moore info			Performance (shifts)	Performance (Time)
	and					16397 3296590, 9.18ms	16397 1163338 19.66ms	16397 1163338 25.946ms		%100					%131.94	
	STAT				26,   3296589, 7.08ms 	26,   831423, 13.25ms	26,   831035, 16.02ms		%99.95					%120.91
	refer				1219, 3296588, 9.91ms	1219, 723973, 12.26ms	1219, 723973, 14.69ms		%100					%119.82
	public				66,   3296587, 7.27ms	66,   599604,  9.61ms	66,   599604, 11.95ms		%100					%124.35
	students			4201, 3296585, 8.43ms	4201, 505340,  9.04ms	4201, 505340, 10.16ms		%100					%112.39
	submission  		74,   3296583, 8.40ms	74,   384247,  7.06ms	74,   384247,  8.69ms		%100					%123.09
	Engineering			258,  3296582, 7.68ms	258,  374720,  6.32ms	258,  372326,  7.65ms		%99.36					%121.04
	Accessibility		125,  3296580, 7.27ms	125,  318729,  5.01ms	125,  318729,  6.07ms		%100					%121.16
	recommendation		80,   3296579, 9.54ms	80,   346519,  6.27ms	80,   333442,  7.17ms		%96.23					%114.35
	characteristics		1,    3296578, 8.14ms	1,    299101,  6.60ms	1.    293298,  6.22ms		%98.06					%94.24
	--------------------------------------------------------------------------------------------------------------------------------------------
	avg																								%99.36					%118.33
	
	********
	Analysis
	********
		From what i have oberved boyermoore and horepool are greatly spead up with larger search terms.
		With boyer-moore the key needs to have repition in order for boyer to really doing anything faster else
		it just slows it down. Brute force seamed to perform consitently. The benifit of boyer-moore over 
		horsepool %1 less shifts vs an %18 gain in time taken.
	
	
**********************************
Assumptions
**********************************
	**The user will not enter a 0 char search term**

**********************************
Source
**********************************
	http://www.inf.fh-flensburg.de/lang/algorithmen/pattern/bmen.htm