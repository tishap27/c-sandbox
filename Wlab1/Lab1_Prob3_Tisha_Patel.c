#include <stdio.h>
#include <stdlib.h>

/* Define macros for leap year conditions */
#define DIVISIBLE_BY_4   ((year) % 4 == 0)
#define DIVISIBLE_BY_100 ((year) % 100 == 0)
#define DIVISIBLE_BY_400 ((year) % 400 == 0)

int main() {
    int year;
    int leap_year;

    /* Prompt user for input */
    printf("Enter year: ");
    scanf("%d", &year);

     /* Check if it's a leap year */
    leap_year = (DIVISIBLE_BY_4 && !DIVISIBLE_BY_100) || DIVISIBLE_BY_400;

    /* Display result */
    if (leap_year) {
        printf("%d is a Leap Year.\n", year);
    } else {
        printf("%d is not a Leap Year.\n", year);
    }

    return EXIT_SUCCESS;
}
