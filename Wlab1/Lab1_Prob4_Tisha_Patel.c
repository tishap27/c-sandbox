#include <stdio.h>
#include <stdlib.h>

/* Define macros for initial Fibonacci values */
#define prev 0 
#define curr 1

int main() {
    int n, i;
    int prev_value = prev, curr_value = curr, next;

     /* Prompt user for input */
    printf("Enter the value of N: ");
    scanf("%d", &n);

    /* Print the header for the Fibonacci sequence */
    printf("Fibonacci Sequence up to %dth term: ", n);

    /* Print first term if n is at least 1 */
    if (n >= 1) {
        printf("%d ", prev_value);
    }

    /* Print second term if n is at least 2 */
    if (n >= 2) {
        printf("%d ", curr_value);
    }

    /* Generate and print the rest of the Fibonacci sequence */
    for (i = 3; i <= n; i++) {
        next = prev_value + curr_value;
        printf("%d ", next);
        prev_value = curr_value;
        curr_value = next;
    }

    return EXIT_SUCCESS;
}
