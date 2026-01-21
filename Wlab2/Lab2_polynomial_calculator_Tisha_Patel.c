#include <stdio.h>
#include <stdlib.h>

/* Macro definitions for menu options and boolean values */
#define ADD '1'
#define EVALUATE '2'
#define EXIT 'X'
#define TRUE 1
#define FALSE 0

/* Function prototypes */
int *InputPolynomial(int degree);
int *addPolynomials(int *poly1, int degree1, int *poly2, int degree2, int *resultDegree);
void displayPolynomial(int *poly, int degree);
int evaluatePolynomial(int *poly, int degree, int x);
void getValidDegree( int *degree1, int *degree2) ;

/* Function to clear input buffer */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Main function */
int main() {
    char choice;
    do {
        printf("\nPolynomial Calculator Menu:\n");
        printf("1. Add Polynomials\n");
        printf("2. Evaluate Polynomials\n");
        printf("X. Exit\n");
        printf("Enter your choice (1/2/X): ");
        scanf(" %c", &choice);

        if (choice == ADD || choice == EVALUATE) {
            int degree1, degree2; 
            int *poly1, *poly2, *resultPoly;
            int resultDegree;

            /* Get valid degrees for polynomials */
            getValidDegree(&degree1, &degree2);
            
            /* Allocate and input coefficients for both polynomials */
            printf("Enter the coefficients for the first polynomial (from highest degree to constant term):\n");
            poly1 = InputPolynomial(degree1);

            printf("Enter the coefficients for the second polynomial (from highest degree to constant term):\n");
            poly2 = InputPolynomial(degree2);

            /* Add polynomials */
            resultPoly = addPolynomials(poly1, degree1, poly2, degree2, &resultDegree);

            if (choice == ADD) {
                /* Display the sum of the polynomials */
                printf("\nSum of the polynomials is: ");
                displayPolynomial(resultPoly, resultDegree);
            } else if (choice == EVALUATE) {
                int x; 
                int result;

                /* Evaluate the sum at a specific value of x */
                printf("Enter the value of x to evaluate the sum of the polynomials: ");
                scanf("%d", &x);
                result = evaluatePolynomial(resultPoly, resultDegree, x);
                printf("The result of the evaluation at x = %d is: %d\n", x, result);
            }

            /* Free allocated memory */
            if (poly1) {
                free(poly1);
                poly1 = NULL;
            }
            if (poly2) {
                free(poly2);
                poly2 = NULL;
            }
            if (resultPoly) {
                free(resultPoly);
                resultPoly = NULL;
            }


        } else if (choice == 'X' || choice == 'x') {
            printf("Exiting the program...\n");
        } else {
            printf("Invalid choice! Please try again. Choose 1,2 or X.\n");
        }
    } while (choice != EXIT && choice != 'x');

    return EXIT_SUCCESS;
}


/*Function to get a valid degree from user. Handles invalid input from user*/
void getValidDegree(int *degree1, int *degree2) {
    do {
        printf("Enter the degree of the first polynomial: ");
        if (scanf("%d", degree1) != 1 || *degree1 < 0) {
            printf("Error: Degree of a polynomial cannot be negative. Please enter a valid degree.\n");
            clearInputBuffer();
            continue;
        }
        break;

    } while (TRUE);
    do {
        printf("Enter the degree of the second polynomial: ");
        if (scanf("%d", degree2) != 1 || *degree2 < 0) {
            printf("Error: Degree of a polynomial cannot be negative. Please enter a valid degree.\n");
            clearInputBuffer();
            continue;
        }
        break;
    } while (TRUE);
    clearInputBuffer();  
}


/* Function to allocate memory and input a polynomial's coefficients */
int *InputPolynomial(int degree) {
    int i;
    int *poly = (int*)malloc((degree + 1) * sizeof(int));
    
    for (i = 0; i <= degree; i++) {
        int valid_input = 0;
        do {
            printf("Enter the coefficient of x^%d: ", degree - i);
            if (scanf("%d", &poly[i]) != 1) {
                while (getchar() != '\n');
                printf("Error: Please enter a valid integer for the coefficient of x^%d.\n", degree - i);
                continue;
                clearInputBuffer();
            } else {
                valid_input = 1;
            }
        } while (!valid_input);
    }
    return poly;
}



/* Function to add two polynomials */
int *addPolynomials(int *poly1, int degree1, int *poly2, int degree2, int *resultDegree) {
    int i; 
    int *resultPoly;
    int isZero;

    /*Ternary operator used to determine the degree of the resulting polynomial*/
    *resultDegree = (degree1 > degree2) ? degree1 : degree2;
    resultPoly = (int *)malloc((*resultDegree + 1) * sizeof(int));

    /* Add coefficients of the polynomials */
    for (i = 0; i <= *resultDegree; i++) {
        int coeff1 = (i <= degree1) ? poly1[degree1 - i] : 0;
        int coeff2 = (i <= degree2) ? poly2[degree2 - i] : 0;
        resultPoly[*resultDegree - i] = coeff1 + coeff2;
    }
     /* Check if the resulting polynomial is zero */
    isZero = 1;
    for (i = 0; i <= *resultDegree; i++) {
        if (resultPoly[i] != 0) {
            isZero = 0;
            break;
        }
    }

    if (isZero) {
        *resultDegree = 0;
        free(resultPoly);
        resultPoly = (int*) malloc(sizeof(int));
        resultPoly[0] = 0;
    }
    return resultPoly;
}



/* Function to display a polynomial*/
void displayPolynomial(int *poly, int degree) {
    int i;
    int isZero;
    isZero = 1;

    for (i = 0; i <= degree; i++) {
        if (poly[i] != 0) {
            isZero = 0;
            break;
        }
    }

    if (isZero) {
        printf("0\n");
        return;
    }

     /* Display non-zero terms of the polynomial */
    for (i = 0; i <= degree; i++) {
        if (poly[i] != 0) {
            if (i > 0 && poly[i] > 0) printf(" + ");
            if (i > 0 && poly[i] < 0) { printf(" - "); poly[i] = -poly[i]; }
            
            if (i < degree - 1) {
                if (poly[i] != 1 && poly[i] != -1) printf("%d", poly[i]);
                printf("x^%d", degree - i);
            } else if (i == degree - 1) {
                if (poly[i] != 1 && poly[i] != -1) printf("%d", poly[i]);
                printf("x");
            } else {
                printf("%d", poly[i]);
            }
        }
    }
    printf("\n");
}



/* Function to evaluate a polynomial using Horner's method */
int evaluatePolynomial(int *poly, int degree, int x) {
    int result = poly[0];
    int i; 
    for (i = 1; i <= degree; i++) {
        /*Horner's method*/
        result = result * x + poly[i]; 
    }
    return result;
}
