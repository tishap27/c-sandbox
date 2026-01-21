
// TM based on DFB's busy beaver

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NSYMB 5
#define FALSE 0
#define TRUE 1
#define ALPHASIZE 2

#define NOFINAL 0
#define SUCCESS 'S'
#define FAILURE 'F'

#define MIN 0
#define MAX 3

#define DEBUG 0
char status = SUCCESS;

// trivial single-card examples
char* TM00 = { "00S1H_01F0H" };
// loops off to the right
char* TM01 = { "0001R_01S0H" };
// loops off to the left
char* TM02 = { "0001L_01S0H" };
// prints a single 1 and moves to the left
char* TM03 = { "0010R_0111L_1001L_11S1H" };
// adder
char* TM04 = { "A0A0R.A1A1R.A_B_L.B0S1H.B1B0L.B_S1H" };

// TM Default
// 00013_01002 00000000000000000000000 (Change 0 to 1 and stop with success)
// 00013_01002 00000000000100000000000 (Change 1 to 0 and stop with failure)
// TM Loop
// 00011_01003 00000000000000000000000 (Write from middle until end with 1's and stop with failure)
// 00010_01003 00000000000000000000000 (Write from middle until beginning with 1's and stop with failure)
// Busybeaver
// 00101_01110_10010_11113 00000000000000000000000
// 00101_01110_10010_11113 00000000000100000000000

char* tm;
char* tape;

int tapesize = 0;
int headpos;
int i;

// print out the tape and on the line below it print out a ^ to show where head pos is for the next read/write
void printtapeTM(void) {
	int i;
	tapesize = (int)strlen(tape);
	for (i = 0; i < tapesize; i++)
		printf("%c ", tape[i]);
	putchar('\n');
	for (i = 0; i < headpos; i++)
		printf("  ");
	putchar('^');
	putchar('\n');
}

// Run TM
int runTuringSteps(char* thistm, int steps) {
	char currtchar, shift;
	int currtcard, nextcard, incdec, currtProd;
	int cursymbindex = 0;
	char currstat, readsymb, nextstat, wrtesymb, diretion;
	nextcard = 0;
	// print out initial deck of cards
	printf("TM: %s\n", thistm);
	currtcard = 0;
	tapesize = (int)strlen(tape);
	headpos = tapesize / 2;
	incdec = 0;
	printf("\nInitial tape (head position marked by ^):\n");
	printtapeTM();
	printf("TM started\n");
	int changed = 0;
	int alphasize = 0;
	char state = thistm[0];
	char newstate = state;
	int curpos = 0;
	int tmlen = (int)strlen(thistm);
	while (newstate == state && curpos < tmlen) {
		alphasize++;
		curpos = curpos + NSYMB + 1;
		newstate = thistm[curpos];
	}
	printf("Number of alphabets: %d\n", alphasize);
	int statesize = ((tmlen + 1) / (NSYMB + 1)) / alphasize;
	printf("Number of states: %d\n", statesize);
	do {
		currtchar = tape[headpos];
		cursymbindex = 0;
		curpos = 0;
		for (i = 0; i < alphasize; i++) {
			curpos = (currtcard * alphasize + i) * (NSYMB + 1) + 1;
			if (thistm[curpos] == currtchar)
				cursymbindex = i;
		}
		currtProd = (currtcard * alphasize + cursymbindex) * (NSYMB + 1);
		currstat = thistm[currtProd];
		diretion = thistm[currtProd + 4];
		shift = diretion - '0';
		///nextcard = thistm[currtProd + 2] - '0';
		nextstat = thistm[currtProd + 2];
		int foundState = 0;
		curpos = 0;
		while (!foundState && curpos<tmlen) {
			if (thistm[curpos] == nextstat) {
				foundState = 1;
				nextcard = curpos / ((NSYMB + 1)* alphasize);
			}
			else {
				curpos = curpos + NSYMB + 1;
			}
		}
		switch (diretion) {
		case 'L':
			incdec = -1;
			break;
		case 'R':
			incdec = 1;
			break;
		default:
			incdec = 0;
		}
		currstat = thistm[currtProd];
		readsymb = thistm[currtProd + 1];
		nextstat = thistm[currtProd + 2];
		wrtesymb = thistm[currtProd + 3];
		diretion = thistm[currtProd + 4];

		tape[headpos] = wrtesymb;
		headpos = headpos + incdec;
		printtapeTM();

		// sanity check
		int upbtape = (int)strlen(tape);
		if ((headpos < 0) || (headpos == upbtape)) {
			printf("[Error]: tape too short and/or TM may be looping\n");
			nextcard = 0;
			nextstat = FAILURE;
		}
		if (DEBUG) {
			printf("[Debug]: Headpos is now %d \n", headpos);
			printf("[Debug]: Current Prod: %d \n", currtProd);
			printf("[TM]: Currstat: %c \n", currstat);
			printf("[TM]: Readsymb: %c \n", readsymb);
			printf("[TM]: Nextstat: %c \n", nextstat);
			printf("[TM]: Wrtesymb: %c \n", wrtesymb);
			printf("[TM]: Direcion: %c \n", diretion);
		}
		currtcard = nextcard;
		steps++;
	} while (nextstat!=SUCCESS && nextstat!=FAILURE);
	status = nextstat;
	return steps;
}

// Execution passing tm and cards
void runTuring(char* tm) {
	int i, score = 0, steps = 0;
	steps = runTuringSteps(tm, steps);
	if (steps == 0)
		printf("The TM has halted\n");
	printf("Final tape config is:\n");
	printtapeTM();
	if (steps != 1) {
		int upbtape = (int)strlen(tape) - 2;
		for (i = 0; i <= upbtape; i++)
			if (tape[i] == '1') score++;
		printf("Steps = %d - score = %d\n", steps, score);
	}
	printf("Final status: %c", status);
	return;
}

void initializeTape() {
	// Tape allocation / initialization
	int upbtape = 25;
	tape = (char*)malloc((upbtape + 1) * sizeof(char));
	if (tape) {
		for (i = 0; i < upbtape; i++) {
			tape[i] = '0';
		}
		tape[upbtape] = '\0';
	}
}

char* initTape(char* str) {
	int size = (int)strlen(str);
	char* myTape = (char*)malloc(size * sizeof(char));
	myTape = str;
	return myTape;
}

// Multiple TM examples
int main(int argc, char** argv) {
	int option = 0;
	int size = 0;
	// Command line parameters
	printf("You have entered %d arguments:\n", argc);
	for (i = 0; i < argc; i++) {
		size = (int)strlen(argv[i]);
		printf("Param %d = %s (size: %d)\n", i, argv[i], size);
	}
	initializeTape();
	switch (argc) {
	case 1:
		/*
		printf("\nTM[04] ..............\n\n");
		char str[] = "_00000000000000000000001_";
		int size = (int)strlen(str);
		tape = (char*)malloc(size * sizeof(char));
		tape = str;
		runTuring((char*)TM04);
		*/
		runTuring((char*)TM00);
		break;
	case 2:
		option = atoi(argv[1]);
		// Switch labs
		printf("COMPILERS EXAMPLES *******************************\n");
		switch (option) {
			// TM Multiple cases
		case 0:
			printf("\nTM[00] ..............\n\n");
			runTuring((char*)TM00);
			break;
		case 1:
			printf("\nTM[01] ..............\n\n");
			runTuring((char*)TM01);
			break;
		case 2:
			printf("\nTM[02] ..............\n\n");
			runTuring((char*)TM02);
			break;
		case 3:
			printf("\nTM[03] ..............\n\n");
			runTuring((char*)TM03);
			break;
		case 4:
			printf("\nTM[04] ..............\n\n");
			tape = initTape("_00000000000000000000001_");
			runTuring((char*)TM04);
			break;
		default:
			printf("No valid TM selected (choose from %d to %d)\n", MIN, MAX);
		}
		break;
	case 3:
		// Example: A0A0R.A1A1R.A_B_L.B0S1H.B1B0L.B_S1H _00000000000000000000001_
		size = (int)strlen(argv[1]);
		tm = (char*)malloc(size * sizeof(char));
		tm = argv[1];
		size = (int)strlen(argv[2]);
		tape = (char*)malloc(size * sizeof(char));
		tape = argv[2];
		runTuring(tm);
		break;
	default:
		printf("Error: Invalid command line parameter!\n");
	}

	// Now run the appropriate BB Turing Machine
	return 0;
}
