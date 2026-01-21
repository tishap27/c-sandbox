/*FUNCTIONS*/
/*use library funstions to calculate sqaure of functions*/
/*functions to calculat eare of circle sqare and rectangle*/
/*Print helloworld count times using recursice function*/
/*sum of n natural numbers*/ /*similarly for factorial*/
/*function for celsius to farenheit*/
/*Fibonacci number*/

#include <stdio.h>

int Fibonacci(int n){
    int Nminus1; 
    int Nminus2;
    int fibN;
    
        if(n==0){
            return 0;
        }
    
        if(n==1){
        return 1;
        }
    
    Nminus1 = Fibonacci(n-1);
    Nminus2 = Fibonacci(n-2);
    fibN = Nminus2+ Nminus1 ;

    
    return fibN; 

}

int main(){
    int n;

    printf("Enter num:");
    scanf("%d", &n);

    printf("The sequence is: %d", Fibonacci(n));


    return 0;
}
















/*#include <stdio.h>

float fareToCels(float temp){
    return (temp -32 )* 0.55;
}
float celsToFare(float temp){
    return (temp *1.8)+32;
}

int main(){
    char stan; 
    float temp;

    printf(" Actual Temp in (F for farenheit and C for celsius)");
    scanf("%c", &stan);


    if(stan=='F'){
        printf("Enter temp in Farenheit:");
        scanf("%f", &temp);
        printf("The temparure converted to celsius is %f : ", fareToCels(temp));

    }
    else if (stan =='C'){
        printf("Enter temp in Celsius:");
        scanf("%f", &temp);
        printf("The temparure converted to Farenheit is %f : ", celsToFare(temp));
    }
    else{
        printf("invalid choice");
    }
    
    printf("Thank you");
    return 0 ; 
}*/























/*#include <stdio.h>

int product(int n ){
    int productNminus1; 
    int productOfN; 

    if(n==1){
        return 1; 
    }
    
    productNminus1 = product(n-1);
    productOfN = productNminus1 * n;

    return productOfN;
}
    int main(){
        int n; 
        printf("Enter n:");
        scanf("%d",&n);

        
        printf("the product of number is %d \n", product(n));
        return 0;
    }*/
















/*#include <stdio.h>

int sum(int n ){
    int sumNminus1; 
    int sumOfN; 

    if(n==1){
        return 1; 
    }
    
    sumNminus1 = sum(n-1);
    sumOfN = sumNminus1 + n;

    return sumOfN;
}
    int main(){
        int n; 
        printf("Enter n:");
        scanf("%d",&n);

        
        printf("the sum of number is %d \n", sum (n));
        return 0;
    }*/





/*#include <stdio.h>

void printHW(int count){
    if (count==0){
        return;
    }
    printf("Hello World \n");
    printHW(count-1); 
}

int main(){
    printHW(5);
    return 0; 

}*/














/*#include <stdio.h>

void areaOfRectangle(int Length, int Breadth){
    printf("The area of rectangle is %d \n", Length * Breadth);
}

void areaOfSquare(int side){
    printf("The area of sqaure is %d \n", side * side);
}

void areaOfCircle(float radius){
    printf("The are of circle is %f \n ", 3.14 *radius*radius); 
}


int main(){
    char shape;
    int Length, side;
    int Breadth;
    float radius; 

    printf("choose shape (R , S, C ):");
    scanf("%c", &shape);

    if (shape=='R'){
    printf("Enter Length:");
    scanf("%d", &Length);

    printf("Enter Breadth:");
    scanf("%d", &Breadth);

    areaOfRectangle(Length, Breadth);

    }
    else if (shape == 'S'){

    printf("Enter side:");
    scanf("%d", &side);
    areaOfSquare(side);
    }

    else if (shape=='C'){
    printf("Enter Radius:");
    scanf("%f", &radius);
    areaOfCircle(radius);
    }
    else {
        printf("Invalid choice");
    }
    

    return 0;
}*/