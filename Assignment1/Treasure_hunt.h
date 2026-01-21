#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#define MIN_MAP_SIZE 2
#define MAX_MAP_SIZE 32
#define MAX_TREASURES 100
#define CODE_LENGTH 4

#define TREASURE_CHAR 'T'
#define EMPTY_CHAR ' '
#define DUG_CHAR '#'
#define FOUND_CHAR '$'
#define CHEAT_CHAR '!'

#define CHECK_ALLOCATION(ptr, msg) if (!(ptr)) { fprintf(stderr, msg); exit(EXIT_FAILURE); }
#define VALIDATE_INPUT(condition, msg) if (!(condition)) { fprintf(stderr, msg); exit(EXIT_FAILURE); }
#define CLEAR_INPUT_BUFFER() while (getchar() != '\n')
#define IS_VALID_COORDINATE(x, y, width, height) ((x) >= 0 && (x) < (width) && (y) >= 0 && (y) < (height))
    


char** createMap(int width, int height);
int isValidTreasureCode(const char* code);
int isDuplicateCode(char** codes, int count, const char* newCode);
char** getTreasureCodes(int treasureCount);
void placeTreasures(char** map, int width, int height, int treasureCount);
void displayMap(char** map, int width, int height, int cheatMode);
void dig(char** map, int x, int y, int* treasuresFound, char** treasureCodes);
void playGame(char** map, int width, int height, int treasureCount, char** treasureCodes);
void freeMemory(char** map, int height, char** treasureCodes, int treasureCount);

#endif /* TREASURE_HUNT_H */