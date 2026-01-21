#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/*Macros used in the program */
#define MENU_INPUT '1'
#define MENU_SOLVE '2'
#define MENU_DISPLAY '3'
#define MENU_EXIT '4'
#define TRUE 1
#define FALSE 0

/*intialized grid to null and size to zero */
int **grid = NULL;
int size = 0;

/* Function prototypes */
int hasDuplicates(int arr[], int size);
int isValidSize(int size);
int validateGrid(void);
void inputSudokuGrid(void);
void printSudokuGrid(void);
int isValid(int row, int col, int num);
int backtrack(int row, int col);
int solveSudoku(void);
void freeMemory(void);

/*Checks for duplicate non-zero values in a 1D array.*/
int hasDuplicates(int arr[], int size) {
    int *seen = (int *)calloc(size + 1, sizeof(int));
    int i;

    if (seen == NULL) {
        perror("Failed to allocate memory for duplicate check");
        return TRUE;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] == 0) continue;
        if (seen[arr[i]]) {
            free(seen);
            return TRUE;
        }
        seen[arr[i]] = 1;
    }

    free(seen);
    return FALSE;
}

/* Checks if the entered size is a valid Sudoku grid size.*/
int isValidSize(int size) {
    int sqrt_size;
    if (size < 1) return FALSE;
    sqrt_size = (int)sqrt(size);
    return (sqrt_size * sqrt_size == size);
}

/* Validates the Sudoku grid for duplicates in rows, columns, and subgrids.*/
int validateGrid(void) {
    int i, j, k, startRow, startCol, subgridSize;
    int *column, *subgrid;

    subgridSize = (int)sqrt(size);

    /* Check rows */
    for (i = 0; i < size; i++) {
        if (hasDuplicates(grid[i], size)) {
            printf("Error: Invalid Sudoku puzzle. Reason: There are duplicate values in row %d.\n", i + 1);
            return FALSE;
        }
    }

    /* Check columns */
    column = (int *)malloc(size * sizeof(int));
    if (column == NULL) {
        perror("Failed to allocate memory for column validation");
        return FALSE;
    }
    for (j = 0; j < size; j++) {
        for (k = 0; k < size; k++) {
            column[k] = grid[k][j];
        }
        if (hasDuplicates(column, size)) {
            printf("Error: Invalid Sudoku puzzle. Reason: There are duplicate values in column %d.\n", j + 1);
            free(column);
            return FALSE;
        }
    }
    free(column);

    /* Check subgrids */
    subgrid = (int *)malloc(size * sizeof(int));
    if (subgrid == NULL) {
        perror("Failed to allocate memory for subgrid validation");
        return FALSE;
    }
    for (startRow = 0; startRow < size; startRow += subgridSize) {
        for (startCol = 0; startCol < size; startCol += subgridSize) {
            int index = 0;
            for (i = startRow; i < startRow + subgridSize; i++) {
                for (j = startCol; j < startCol + subgridSize; j++) {
                    subgrid[index++] = grid[i][j];
                }
            }
            if (hasDuplicates(subgrid, index)) {
                printf("Error: Invalid Sudoku puzzle.\nReason: There are duplicate values in subgrid (rows %d-%d, columns %d-%d).\n",
                       startRow + 1, startRow + subgridSize,
                       startCol + 1, startCol + subgridSize);
                free(subgrid);
                return FALSE;
            }
        }
    }
    free(subgrid);

    return TRUE;
}

/*function to clear Buffer */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Takes the Sudoku grid input from the user as a single block of numbers.*/
void inputSudokuGrid() {
    int i, j, num_read;
    printf("Enter the Sudoku puzzle row by row, with 0 representing an empty cell:\n");
    /*reads input in one go */
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            num_read = scanf("%d", &grid[i][j]);
            if (num_read != 1) {
                printf("Error: Invalid input. Please enter only integers.\n");
                /* Clear input buffer*/ 
                while (getchar() != '\n');
                i = -1; /*Restart input*/ 
                j = size;
                break;
            }
            if (grid[i][j] > size || grid[i][j] < 0) {
                printf("Error: Invalid input. Numbers must be between 0 and %d.\n", size);
                /* Clear input buffer*/
                while (getchar() != '\n');
                i = -1; /*Restart input*/
                j = size;
                break;
            }
        }
        if(i == -1) break;
    }
}
/*Displays the current state of the Sudoku grid to the console.*/
void printSudokuGrid(void) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }
}

/*Checks if a given number can be placed in a specific cell without violating Sudoku rules.*/
int isValid(int row, int col, int num) {
    int i, j, startRow, startCol, subgridSize;

    /* Check row and column */
    for (i = 0; i < size; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return FALSE;
    }

    /* Check subgrid */
    subgridSize = (int)sqrt(size);
    startRow = row - row % subgridSize;
    startCol = col - col % subgridSize;

    for (i = 0; i < subgridSize; i++) {
        for (j = 0; j < subgridSize; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return FALSE;
        }
    }

    return TRUE;
}

/*Recursive backtracking function to solve the Sudoku puzzle.*/
int backtrack(int row, int col) {
    int num;

    if (col == size) {
        col = 0;
        row++;
        if (row == size)
            return TRUE;
    }

    if (grid[row][col] != 0)
        return backtrack(row, col + 1);

    for (num = 1; num <= size; num++) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;

            if (backtrack(row, col + 1))
                return TRUE;

            grid[row][col] = 0;
        }
    }

    return FALSE;
}

/*Solves the Sudoku puzzle by calling the backtrack() function.*/
int solveSudoku(void) {
    if (!validateGrid()) {
        return FALSE;
    }

    if (!backtrack(0, 0)) {
        printf("No solution exists for this Sudoku puzzle.\n");
        return FALSE;
    }

    printf("Sudoku puzzle solved successfully!\n");
    return TRUE;
}
int initializeGrid(void)
{
    int i, j;

    printf("Enter the size of Sudoku grid (e.g., 9 for 9x9): ");
    if (scanf("%d", &size) != 1 || !isValidSize(size)) {
        clearInputBuffer();
        printf("Error: Invalid size. Please enter a valid Sudoku grid size (perfect square).\n");
        return FALSE;
    }
    clearInputBuffer();

    /* Allocate memory for the grid */
    grid = (int **)malloc(size * sizeof(int *));
    if (grid == NULL) {
        perror("Failed to allocate memory for grid");
        return FALSE;
    }

    for (i = 0; i < size; i++) {
        grid[i] = (int *)malloc(size * sizeof(int));
        if (grid[i] == NULL) {
            perror("Failed to allocate memory for grid row");
            freeMemory(); /* Free already allocated memory */
            return FALSE;
        }
        /* Initialize all cells in the row to zero */
        for (j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }

    return TRUE;
}
/*function to display menu only prints out menu*/
void displayMenu(void)
{
    printf("Sudoku Menu System:\n");
    printf("1. Input Sudoku\n");
    printf("2. Solve current puzzle\n");
    printf("3. Display puzzle\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

/*Frees the dynamically allocated memory for the Sudoku grid.*/
void freeMemory(void) {
    int i;

    for (i = 0; i < size; i++) {
        free(grid[i]);
    }
    
    free(grid);
}

/*The main function of the Sudoku solver program.*/
int main(void)
{
    char choice;
    int puzzleEntered = FALSE; /* Flag to track if a puzzle has been entered */

    /* Prompt for grid size */
    if (!initializeGrid()) {
        return EXIT_FAILURE; /* Exit if grid initialization fails */
    }

    /* Main menu loop */
    do {
        displayMenu(); /* Display the menu */

        if (scanf(" %c", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number between 1-4.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case MENU_INPUT:
                inputSudokuGrid(); /* Input the puzzle */
                puzzleEntered = TRUE;
                break;

            case MENU_SOLVE:
                if (!puzzleEntered) {
                    printf("Error: No Sudoku puzzle entered yet. Please input a puzzle first.\n");
                } else {
                    solveSudoku();
                }
                break;

            case MENU_DISPLAY:
                if (!puzzleEntered) {
                    printf("Error: No Sudoku puzzle entered yet. Please input a puzzle first.\n");
                } else {
                    printSudokuGrid();
                }
                break;

            case MENU_EXIT:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter number between 1-4.\n");
        }
    } while (choice != MENU_EXIT);

    freeMemory(); /* Free allocated memory before exiting */
    return EXIT_SUCCESS;
}
