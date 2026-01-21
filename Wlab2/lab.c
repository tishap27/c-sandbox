#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_DEGREE 100

void clearInputBuffer();
int* inputPolynomial(int* degree);
int* addPolynomial(int* poly1, int degree1, int* poly2, int degree2, int* resultDegree);
void displayPolynomial(int* poly, int degree);
int evaluatePoly(int* poly, int degree, int x);
int getValidInteger(const char* prompt);

int main() {
    char choice;
    int i;
    
    do {
        printf("Polynomial Calculator Menu:\n");
        printf("1. Add Polynomials\n");
        printf("2. Evaluate Polynomials\n");
        printf("X. Exit\n");
        printf("Enter your choice (1/2/X): ");
        scanf(" %c", &choice);
        clearInputBuffer();

        if (choice == '1' || choice == '2') {
            int degree1, degree2;
            int *poly1, *poly2, *resultPoly;
            int resultDegree;

            poly1 = inputPolynomial(&degree1);
            poly2 = inputPolynomial(&degree2);

            resultPoly = addPolynomial(poly1, degree1, poly2, degree2, &resultDegree);

            if (choice == '1') {
                printf("Sum of polynomials is: ");
                displayPolynomial(resultPoly, resultDegree);
            } else {
                int x = getValidInteger("Enter the value of x to evaluate the sum of the polynomials: ");
                int result = evaluatePoly(resultPoly, resultDegree, x);
                printf("The result of the evaluation at x = %d is: %d\n", x, result);
            }

            free(poly1);
            free(poly2);
            free(resultPoly);

        } else if (choice == 'X' || choice == 'x') {
            printf("Exiting the program...\n");
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 'X' && choice != 'x');
    
    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInteger(const char* prompt) {
    int value;
    char input[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            char* endptr;
            value = strtol(input, &endptr, 10);
            if (endptr != input && (*endptr == '\n' || *endptr == '\0')) {
                return value;
            }
        }
        printf("Error: Please enter a valid integer.\n");
    }
}

int* inputPolynomial(int* degree) {
    int *poly;
    int i;
    *degree = getValidInteger("Enter the degree of the polynomial: ");
    while (*degree < 0 || *degree > MAX_DEGREE) {
        printf("Error: Degree must be between 0 and %d.\n", MAX_DEGREE);
        *degree = getValidInteger("Enter the degree of the polynomial: ");
    }

     poly = (int*)malloc((*degree + 1) * sizeof(int));
    for ( i = *degree; i >= 0; i--) {
        poly[i] = getValidInteger("Enter coefficient of x^%d: ", i);
    }
    return poly;
}

int* addPolynomial(int* poly1, int degree1, int* poly2, int degree2, int* resultDegree) {
    *resultDegree = (degree1 > degree2) ? degree1 : degree2;
    int *resultPoly;
     resultPoly = (int*)calloc(*resultDegree + 1, sizeof(int));
    int i;

    for ( i = 0; i <= *resultDegree; i++) {
        int coef1 = (i <= degree1) ? poly1[i] : 0;
        int coef2 = (i <= degree2) ? poly2[i] : 0;
        resultPoly[i] = coef1 + coef2;
    }
    return resultPoly;
}

void displayPolynomial(int* poly, int degree) {
    int first = 1;
    int i;
    for ( i = degree; i >= 0; i--) {
        if (poly[i] != 0) {
            if (!first) {
                printf(poly[i] > 0 ? " + " : " - ");
            } else if (poly[i] < 0) {
                printf("-");
            }
            first = 0;

            int absCoef = abs(poly[i]);
            if (absCoef != 1 || i == 0) {
                printf("%d", absCoef);
            }
            if (i > 0) {
                printf("x");
                if (i > 1) {
                    printf("^%d", i);
                }
            }
        }
    }
    if (first) {  
        printf("0");
    }
    printf("\n");
}

int evaluatePoly(int* poly, int degree, int x) {
    int result = poly[degree];
    int i;
    for ( i = degree - 1; i >= 0; i--) {
        result = result * x + poly[i];
    }
    return result;
}
