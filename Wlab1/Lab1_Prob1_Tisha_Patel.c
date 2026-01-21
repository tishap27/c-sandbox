#include <stdio.h>
#include <stdlib.h>

/* Define macros for operation codes */
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

int main() {
    int num1, num2, operation, result;

    /* Input first number */
    printf("Enter first number: ");
    scanf("%d", &num1);

    /* Input second number */
    printf("Enter second number: ");
    scanf("%d", &num2);

    /* Input operation choice */
    printf("Select operation (1 for ADD, 2 for SUB, 3 for MUL, 4 for DIV): ");
    scanf("%d", &operation);

    /* Performing the selected operation and displays the result */
    if (operation == ADD) {
        result = num1 + num2;
        printf("Result: %d + %d = %d\n", num1, num2, result);
    }
    else if (operation == SUB) {
        result = num1 - num2;
        printf("Result: %d - %d = %d\n", num1, num2, result);
    }
    else if (operation == MUL) {
        result = num1 * num2;
        printf("Result: %d * %d = %d\n", num1, num2, result);
    }
    else if (operation == DIV) {
        /* Checks for division by zero */
        if (num2 != 0) {
            result = num1 / num2;
            printf("Result: %d / %d = %d\n", num1, num2, result);
        }
        else {
            printf("Error: Division by zero is not allowed!\n");
        }
    }
    else {
         /* Handles invalid operation selection */
        printf("Error: Invalid operation selected!\n");
    }

    return EXIT_SUCCESS;
}
