/* 
 * Treasure Hunt Game
 * Author: [Tisha Patel]
 * Student ID: [041133762]
 * 
 * This Assignment implements a treasure hunt game where players
 * dig for hidden treasures on a 2D map.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Treasure_hunt.h"


/* 
 * Creates a 2D map of given width and height
 * Returns: Dynamically allocated 2D char array
 */
char** createMap(int width, int height)
{
    int i;
    char** map = (char**)malloc(height * sizeof(char*));
    CHECK_ALLOCATION(map, "Memory allocation failed for map rows.\n");

    for (i = 0; i < height; i++) {
        map[i] = (char*)malloc(width * sizeof(char));
        CHECK_ALLOCATION(map[i], "Memory allocation failed for map columns.\n");
        memset(map[i], EMPTY_CHAR, width);
    }
    return map;
}

/* 
 * Validates if the given code is a valid treasure code
 * Returns: 1 if valid, 0 otherwise
 */
int isValidTreasureCode(const char* code)
{
    int i;
    if (strlen(code) != CODE_LENGTH || code[0] != TREASURE_CHAR)
    return EXIT_SUCCESS;
    for (i = 1; i < CODE_LENGTH; i++) {
        if (code[i] < '0' || code[i] > '9')
        return EXIT_SUCCESS;    
    }
    return EXIT_FAILURE;
}

/* 
 * Checks if the given code is a duplicate
 * Returns: 1 if duplicate, 0 otherwise
 */
int isDuplicateCode(char** codes, int count, const char* newCode)
{
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(codes[i], newCode) == 0)
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* 
 * Gets treasure codes from user input
 * Returns: Array of treasure codes
 */
char** getTreasureCodes(int treasureCount)
{
    int i;
    char** codes = (char**)malloc(treasureCount * sizeof(char*));
    CHECK_ALLOCATION(codes, "Memory allocation failed for treasure codes.\n");

    for (i = 0; i < treasureCount; i++) {
        codes[i] = (char*)malloc(CODE_LENGTH + 1);
        CHECK_ALLOCATION(codes[i], "Memory allocation failed for treasure code.\n");

        while (1) { /* Loop until a valid code is entered*/
            printf("Enter treasure #%d code (e.g., T001): ", i + 1);
            if (scanf("%4s", codes[i]) != 1) {
                if (feof(stdin)) {
                    /* Free allocated memory before exit */
                    while (i >= 0) {
                        free(codes[i]);
                        i--;
                    }
                    free(codes);
                    exit(EXIT_SUCCESS);
                }
                printf("Invalid input. Try again.\n");
                CLEAR_INPUT_BUFFER();
                continue;
            }

            /*Check if the code is valid*/
            if (!isValidTreasureCode(codes[i])) {
                printf("Treasure codes must be a 'T' followed by 3 digits.\n");
                continue; 
            }

            /* Check for duplicates*/
            if (isDuplicateCode(codes, i, codes[i])) {
                printf("Treasure code already in use.\n");
                continue; 
            }

            break; 
        }
    }
    return codes;
}


/* 
 * Places treasures randomly on the map
 */
void placeTreasures(char** map, int width, int height, int treasureCount)
{
    int i, x, y;
    srand((unsigned int)time(NULL)); /*seeds ramdom number genretao with current time*/
    for (i = 0; i < treasureCount; i++) {
        do {
            x = rand() % width;
            y = rand() % height;
        } while (map[y][x] != EMPTY_CHAR);
        map[y][x] = TREASURE_CHAR;
    }
}


/* 
 * Displays the current state of the map
 */
void displayMap(char** map, int width, int height, int cheatMode)
{
    int x, y;
    printf("Map:\n   ");
    for( x= 0; x<width; x++)printf("%d",x/10);
    printf("\n   ");
    for (x = 0; x < width; x++) printf("%d", x % 10);
    printf("\n   ");
    for (x = 0; x < width; x++) printf("-");
    printf("\n");

    for (y = 0; y < height; y++) {
        printf("%2d|", y);
        for (x = 0; x < width; x++) {
            char displayChar = map[y][x];
            if (!cheatMode && displayChar == TREASURE_CHAR) displayChar = EMPTY_CHAR;
            else if (cheatMode && displayChar == TREASURE_CHAR) displayChar = CHEAT_CHAR;
            printf("%c", displayChar);
        }
        printf("|\n");
    }
}
/* 
 * Performs the digging action at the specified coordinates
 */
void dig(char** map, int x, int y, int* treasuresFound, char** treasureCodes)
{
    if (map[y][x] == EMPTY_CHAR) {
        map[y][x] = DUG_CHAR;
        printf("You found nothing there!\n");
    } else if (map[y][x] == TREASURE_CHAR) {
        map[y][x] = FOUND_CHAR;
        printf("Congratulations, you found a treasure! Code: %s\n", treasureCodes[(*treasuresFound)++]);
    } else {
        printf("You already dug here!\n");
    }
}

/* 
 * Main game loop
 */
void playGame(char** map, int width, int height, int treasureCount, char** treasureCodes)
{
    int treasuresFound = 0;
    int cheatMode = 0;
    int choice, x, y;

    while (treasuresFound < treasureCount) {
        displayMap(map, width, height, cheatMode);
        printf("1 - Dig | 2 - Exit | 3 - Cheat\n-> ");
        
        if (scanf("%d", &choice) != 1) {
            if (feof(stdin)) {
                printf("End of input reached. Exiting game.\n");
                return;
            }
            printf("Invalid input. Try again.\n");
            CLEAR_INPUT_BUFFER();
            continue;
        }

        switch (choice) {
            case 1:
                do {
                    printf("Where would you like to dig?\n");
                    printf("x = ");
                    if (scanf("%d", &x) != 1) {
                        if (feof(stdin)) {
                            printf("End of input reached. Exiting game.\n");
                            return;
                        }
                        printf("Invalid input for x-coordinate. Try again.\n");
                        CLEAR_INPUT_BUFFER();
                        continue;
                    }
                    if (x < 0 || x >= width) {
                        printf("Invalid x-coordinate. Must be between 0 and %d.\n", width - 1);
                        continue;
                    }

                    printf("y = ");
                    if (scanf("%d", &y) != 1) {
                        if (feof(stdin)) {
                            printf("End of input reached. Exiting game.\n");
                            return;
                        }
                        printf("Invalid input for y-coordinate. Try again.\n");
                        CLEAR_INPUT_BUFFER();
                        continue;
                    }
                    if (y < 0 || y >= height) {
                        printf("Invalid y-coordinate. Must be between 0 and %d.\n", height - 1);
                        continue;
                    }

                    break; 
                } while (1);

                dig(map, x, y, &treasuresFound, treasureCodes);
                break;
        
            case 2:
                printf("Thanks for playing!\n");
                return;
            case 3:
                cheatMode = !cheatMode;
                printf("CHEAT mode %s!\n", cheatMode ? "enabled" : "disabled");
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
    printf("Congratulations! You found all the treasures!\n");
}

/* 
 * Frees all dynamically allocated memory
 */
void freeMemory(char** map, int height, char** treasureCodes, int treasureCount)
{
    int i;
    for (i = 0; i < height; i++) free(map[i]);
    free(map);
    
    for (i = 0; i < treasureCount; i++) free(treasureCodes[i]);
    free(treasureCodes);
}

int main(void)
{
    int width, height, treasureCount;
    char** map;
    char** treasureCodes;

    printf("Enter Map Width: ");
    VALIDATE_INPUT(scanf("%d", &width) == 1 && width >= MIN_MAP_SIZE && width <= MAX_MAP_SIZE,
                   "Invalid map width.\n");

    printf("Enter Map Height: ");
    VALIDATE_INPUT(scanf("%d", &height) == 1 && height >= MIN_MAP_SIZE && height <= MAX_MAP_SIZE,
                   "Invalid map height.\n");

    printf("Enter number of treasures: ");
    VALIDATE_INPUT(scanf("%d", &treasureCount) == 1 && treasureCount >= 1 && treasureCount <= MAX_TREASURES,
                   "Invalid number of treasures.\n");

    map = createMap(width, height);
    treasureCodes = getTreasureCodes(treasureCount);
    
    placeTreasures(map, width, height, treasureCount);

    playGame(map, width, height, treasureCount, treasureCodes);

    freeMemory(map, height, treasureCodes, treasureCount);

    return EXIT_SUCCESS;
}