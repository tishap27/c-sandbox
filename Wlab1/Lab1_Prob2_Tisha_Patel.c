#include <stdio.h>
#include <stdlib.h>

/* Define macros for BMI categories thresholds */
#define UNDERWEIGHT 18.5
#define NORMAL 25
#define OVERWEIGHT 30


int main() {
    float weight, height, bmi;

     /* Input weight */
    printf("Enter weight in kilograms: ");
    scanf("%f", &weight);

     /* Input height */
    printf("Enter height in meters: ");
    scanf("%f", &height);

    /* Validate input */
     if (weight <= 0 || height <= 0) {
        printf("Error: Weight and height must be greater than 0!\n");
        return EXIT_FAILURE;
    }

    /* Calculate BMI */
    bmi = weight / (height * height);

    /* Display BMI */
    printf("BMI = %.2f\n", bmi);

    /* Determine and display BMI category */
    printf("Category: ");
    if (bmi < UNDERWEIGHT) {
        printf("Underweight\n");
    } else if (bmi < NORMAL) {
        printf("Normal weight\n");
    } else if (bmi < OVERWEIGHT) {
        printf("Overweight\n");
    } else {
        printf("Obese\n");
    }

    return EXIT_SUCCESS;
}
