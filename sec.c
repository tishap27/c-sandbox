/*POINTERS*/
/*print value of i form its pointer to pointer */
/* swap values of a and b */
/* calculate sum, product, and average of 2 numbers. print them in main function*/

/*ARRAY*/
/*array has n values how to print htose values */
/*store 2 studentts ke three subject ke marks*/
/*write func to count odd numbers using array*/
/*write a function to reverse an  array*/
/*store fibonacci numbers*/
/*create 2D array to store tables of 2 and 3 */

#include <stdio.h>


void storeTable(int table[][10], int n , int m, int number){
    int i; 
    for(i=0;i<m; i++){
        table[n][i]=number *(i+1);
    }
}

int main(){
    int i;
    int table[2][10];
    storeTable(table, 0, 10, 2);
    storeTable(table, 1, 10, 3);

    for(i=0; i<10;i++){
        printf("%d \t ", table[0][i]);
        
    }
    printf("\n");
    for(i=0; i<10;i++){
    printf("%d \t", table[1][i]);
    }
    printf("\n");



    return 0; 
}




























/*#include <stdio.h>

void storeTables(int table[][10], int n, int m , int num ){
    int i;
    for(i=0; i<m; i++){
        table[n][i]= num * (i+1);
    }

}

int main(){
    int i ;
    int tables[2][10];
    storeTables(tables, 0 , 10, 2);
    storeTables(tables, 1 , 10, 3);

    for(i=0;i<10;i++){
        printf("%d \t", tables[0][i]);
    }

    printf("\n");

    for(i=0;i<10;i++){
        printf("%d \t", tables[1][i]);
    }
    printf("\n");

    return 0;
}*/

















/*int main(){
    int n, i ; 

    printf("Enter num (num>2):");
    scanf("%d", &n); 

    int fib[n];
     fib[0]= 0;
     fib[1]= 1;

     for( i = 2; i<n ; i++){
        fib[i]= fib[i-1]+ fib[i-2];
        printf("%d \t", fib[i]);
     }
    printf("\n");
    return 0; 
}*/
















/*void reverse(int arr[], int n ){
    
    int i ; 

    for(i=1; i< (n/2); i++){
    int firstVal = arr[i];
    int secondVal= arr[n-i-1];

    arr[i]= secondVal;
    arr[n-i-1]= firstVal;

    }
}

void printArr(int arr[], int n ){
        
        int i ; 
        for (i=0;  i<n; i++){
            printf("%d  \t", arr[i]);
            
        }
        printf("\n");
    }


int main (){
     
     int arr[]= {1,2,3,4,5,6};

     reverse(arr, 6 ); 
     printArr(arr, 6);
     

    return 0 ; 
}*/




















/*#include <stdio.h>

int countOdd(int arr[], int n ){

    int count = 0 ; 
    int i; 

    for(i=0; i<=n;i++){
        if(arr[i] % 2 != 0 ){
            count++ ; 
        }
    }
        return count;
        printf("Thank you \n");
}

int main(){
     int arr[]= {1,2,3,4,5,6};

     
     printf("the count is : %d \n", countOdd(arr, 6 ));

    return 0; 
}
*/
















/*void printNum(int *num, int n){
    int  i;
    for (i=0; i<n; i++){
        printf("%d \t", num[i]);

    }
    printf("\n");

}

int main(){
    int num[]= {1,2,3,4,5,6};
    printNum(num , 6);

    

    return 0 ;

}*/














/*int main(){
int aadhar[5];
int i ; 

int *ptr = &aadhar ; 
for(i=0; i< 5; i++){
    printf("%d index: ", i ); 
    scanf("%d", (ptr+i));

}
for(i=0 ;i<5;i++){
    printf("%d index : %d \n" , i, *(ptr+i));
}

    return 0;
}*/








/*int main(){
    
    int age = 22; 
    int _age = 23;
    int *ptr = &age;
    int *_ptr= &_age;
    printf(" %u , %u \n difference %d \n", ptr, _ptr,  ptr-_ptr);
    _ptr = &age;
    printf("compare %u \n", ptr == _ptr);

    return 0;
}*/







/*int main(){
     
     float price[3];
     int totalPrice1; 
     int totalPrice2;
     int totalPrice3;

    float price[]= {100.0, 200.0, 300.0 };
     printf("Enter price1: ");
     scanf("%f", &price[0]);

     printf("Enter price2: ");
     scanf("%f", &price[1]);

     printf("Enter price3: ");
     scanf("%f", &price[2]);

    printf("totalPrice1 = %f\n ",price[0]+(0.18*price[0])); 
    printf("totalPrice2 = %f\n ",price[1]+(0.18*price[1]));
    printf("totalPrice3 = %f\n ", price[2]+(0.18*price[2]));
    
     printf("Total price is : %d\n", totalPrice1+totalPrice2+totalPrice3);



    return 0; 
}*/












/*int main(){

    int marks[3];

    printf("Enter math marks:");
    scanf("%d", &marks[0]);

    printf("Enter phy marks:");
    scanf("%d", &marks[1]);

    printf("Enter chem marks:");
    scanf("%d", &marks[2]);

    printf("Math = %d, Phy = %d, chem = %d\n", marks[0], marks[1], marks[2]);

    return 0;
}*/

















/*#include <stdio.h>

void doWork( int a , int b , int  *sum , int *prod, int *avg){

        *sum = a+b ; 
        *prod = a*b; 
        *avg = (a+b)/2;
}

int main(){
    int a = 3, b = 5;
    int sum, prod, avg;
    doWork(a,b , &sum, &prod , &avg);
    printf("sum is %d, product is: %d, average is: %d", sum , prod, avg);

    return 0 ; 
}*/






/*#include <stdio.h>

void swap(int a , int b ){
    int t = a; 
        a = b; 
        b = t;

        printf(" Call by value \n a = %d , b = %d\n", a, b); 

}

void _swap(int *a , int *b){
    int t = *a; 
        *a = *b;
        *b = t; 

        printf(" Call by reference \n a = %d , b = %d\n", *a, *b );

}
int main (){
    int a = 3, b=5; 

    swap(a,b);
    printf(" Call by value \n a = %d , b = %d\n", a, b);

    _swap(&a, &b);
    printf(" Call by reference \n a = %d , b = %d\n", a , b);


    return 0 ;
}*/





















/*call be refrence*/
/*void _swap(int *a , int *b ){
    int t = *a;
        *a = *b; 
        *b = t; 
     printf("a = %d , b= %d \n", *a , *b);

} 
call by value 
void swap (int a , int b ){
    int t = a;
        a = b;
        b = t;
        
        printf("a = %d , b= %d \n ", a , b );
        
}
int main(){
    int a = 3 ;
    int b = 5 ;

    swap(a,b);
    printf("x = %d, y = %d \n" , a , b );

    _swap(&a,&b);
    printf("x = %d, y = %d \n" , a , b );
    return 0; 

} */


/*void square(int n ){
    n = n* n ; 
    printf("Square is : %d\n", n);

}
void _square(int *n){
    *n=(*n) *(*n);
     printf("Square is : %d\n", *n);

}

int main(){

    int number= 4; 
    square(number);
    printf("Number is : %d\n", number);

    _square(&number);
    printf("number is: %d\n", number);
    return 0;
}*/










/*int main(){
    int i=5; 
    int *ptr = &i;
    int **pptr = &ptr;

    printf("%d \n ", &ptr);
    return 0;
}*/
