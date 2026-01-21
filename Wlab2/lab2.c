/*lab2 input poly , Add poly, evaluate poly, display poly*/

#include <stdio.h>
#include <stdlib.h>

#define ADD '1'
#define EVALUATE '2'
#define EXIT 'X'
#define MAX_DEGREE '100'

#define HIGHEST_DEGREE_INDEX 0
#define COEFF_ONE 1

int *inputPolynomial(int degree);
int *addPolynomial(int *poly1, int degree1, int *poly2, int degree2, int *resultDegree);
void displayPolynomial(int *poly, int degree);
int evaluatePoly(int *poly, int degree, int x);


int main(){
    char choice;
    
    do
    {
        printf("Polynomial Calculator Menu:\n");
        printf("1. Add Polynomials\n");
        printf("2. Evaluate Polynomials\n");
        printf("X. Exit\n");
        printf("Enter your choice(1/2/X):");
        scanf("%c",&choice);
        

        if(choice == ADD || choice == EVALUATE){
            int degree1, degree2;
            int *poly1 , *poly2 , *resultPoly;
            int resultDegree;


            printf("Enter the degree of the first polynomial:");
            scanf("%d", &degree1);
            if(scanf("%d", &degree1) != 1 || degree1 < 0 || degree1 > MAX_DEGREE) {
                printf("Invalid degree. Please enter a number between 0 and %d.\n", MAX_DEGREE);
                
                continue;
            }

            printf("Enter the degree of the second polynomial:");
            scanf("%d", &degree2);
            if(scanf("%d", &degree2) != 1 || degree1 < 0 || degree1 > MAX_DEGREE) {
                printf("Invalid degree. Please enter a number between 0 and %d.\n", MAX_DEGREE);
                
                continue;
            }

            printf("Enter the coefficients for the first polynomial (from highest degree to constat term):\n");
            poly1 = inputPolynomial(degree1);

            printf("Enter the coefficients for the second polynomial (from highest degree to constat term):\n");
            poly2 = inputPolynomial(degree2);

            resultPoly = addPolynomial(poly1, degree1, poly2, degree2, &resultDegree);

            if(choice == ADD){
                printf("Sum of polynomials is:");
                displayPolynomial(resultPoly, resultDegree);

            }
            else if(choice == EVALUATE){
                int x;
                int result; 

                printf("Enter the value of x to evaluate the sum of the polynomials:");
                scanf("%d", &x);

                result = evaluatePoly(resultPoly, resultDegree, x);
                printf("The result of the evaluation at x = %d is: %d\n", x, result);

            }
            free(poly1);
            free(poly2);
            free(resultPoly);

        } else if (choice == EXIT || choice == 'x') {
            printf("Exiting the program...\n");
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != EXIT && choice !='x');
    
    return EXIT_SUCCESS; 
}




int *inputPolynomial(int degree ){
    int i;
     
    int *poly = (int*)malloc((degree + 1) * sizeof(int));
    for (i=0; i<=degree; i++){
        printf("Enter the coefficient of x^%d: ", degree-i);
        scanf("%d", &poly[i]);
    }
    return poly;
}


int *addPolynomial(int *poly1 ,int degree1,int *poly2 , int degree2, int *resultDegree){
    int *resultPoly;
    int i ;
    int isZero;


    *resultDegree = (degree1 > degree2) ? degree1 : degree2 ; 

    resultPoly = (int*) malloc((*resultDegree+1) * sizeof(int));

    for(i=0; i<=*resultDegree;i++){

        int coef1 = (i <= degree1) ? poly1[degree1 - i] : 0;
        int coef2 = (i <= degree2) ? poly2[degree2 - i] : 0;

        resultPoly[*resultDegree - i] = coef1 + coef2;
    }  
    /* Check if the result is a zero polynomial*/
    
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

    for (i = 0; i <= degree; i++) {
        if (poly[i] != 0) {
            if (i > 0 && poly[i] > 0) printf(" + ");
            if (i > 0 && poly[i] < 0) { printf(" - "); poly[i] = -poly[i]; }
            
            if (i < degree && poly[i] != 1) printf("%dx^%d", poly[i], degree - i);
            else if (i < degree && poly[i] == 1) printf("x^%d", degree - i);
            else printf("%d", poly[i]);
        }
    }
    printf("\n");
}

int evaluatePoly(int *poly , int degree, int x){
    int result = poly[0];
    int i;
    for(i=1 ; i <= degree; i++){
        result = result * x + poly[i];
    }
    return result;
}

/*void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}*/


