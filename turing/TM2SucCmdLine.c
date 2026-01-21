#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAPE_SIZE 100
#define TRANSITIONS 6

typedef struct {
    char currentState;
    char currentSymbol;
    char nextState;
    char nextSymbol;
    char direction;
} Transition;

Transition transitions[TRANSITIONS] = {
  {'I', '0', 'I', '0', 'R'}, // Move right on 0
  {'I', '1', 'I', '1', 'R'}, // Move right on 1
  {'I', '_', 'A', '_', 'L'}, // Blank space, go left
  {'A', '0', 'S', '1', 'R'}, // Change 0 to 1, success
  {'A', '1', 'A', '0', 'L'}, // Change 1 to 0, move left
  {'A', '_', 'S', '1', 'R'}  // Add 1 to the beginning
};

// Function to simulate the Turing machine
void runTuringMachine(char* tape) {
  char currentState = 'I';
  int i, headPosition = 0, transitionFound;
  while (1) {
    transitionFound = 0;
    for (i = 0; i < TRANSITIONS; i++) {
      if (transitions[i].currentState == currentState &&
          transitions[i].currentSymbol == tape[headPosition]) {
        tape[headPosition] = transitions[i].nextSymbol;
        currentState = transitions[i].nextState;
        printf("(%c,%c,%c,%c,%c):CState=%c, CSymbol=%c -> %s\n",
            transitions[i].currentState, transitions[i].currentSymbol,
            transitions[i].nextState, transitions[i].nextSymbol,
            transitions[i].direction, currentState, 
            tape[headPosition], tape);
        if (transitions[i].nextState == 'S') {
          printf("Success: %s\n", tape);
          return;
        }
        if (transitions[i].direction == 'L')
          headPosition--;
        else if (transitions[i].direction == 'R')
          headPosition++;
        transitionFound = 1;
        break;
      }
    }
    if (!transitionFound) {
      printf("Fail\n");
      return;
    }
  }
}

// Main function
int main(int argc, char *argv[]) {
  int i = 0;
  char *tape = malloc(TAPE_SIZE);
  char stdtape[TAPE_SIZE] = "1101_";
  if (argc>1) {
	  size_t length = strlen(argv[1])+1;
	  printf("Size of the input: %d\n", length);
	  tape = malloc(length);
	  for (i=0;i<length;i++)
		  tape[i] = argv[1][i];
	  tape[length] = '\0';
  } else {
	  tape = malloc(TAPE_SIZE);
	  for (i=0;i<TAPE_SIZE;i++)
		  tape[i] = stdtape[i];
  }
  printf("Initial tape: %s\n", tape);
  runTuringMachine(tape);
  return 0;
}
