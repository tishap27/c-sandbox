#include <stdio.h>
#include <stdlib.h>


int main(){
    int num;
    int i;
    printf("Enter num:");
    scanf("%d", &num);

    if (num<0){
        printf("INVALID");
       
    }
    else {
        for(i=2; i*i<=num;i++){
            if(num % i == 0 ){ /*if divided by i not prime*/
            printf("not prime");
            } else {
            printf("Prime");
            }
        
        }   
    }
    return 0;
}
/*void func(int *p) {
    int *q = 10;
    *p = &q;
}

int main() {
    int r = 20;
    int *p = &r;
    func(&p);
    printf("%d", *p);
    return 0;
}*/


/*int *returnPointer(){
    int *ptr =(int*)malloc(sizeof(int));
    *ptr =10;
    return ptr;
}
int main(){
    returnPointer();
    return 0;
}*/

/*int* arrayPointer(){
     int x=10;
    return &x;
}
int main()
{
    int *ptr = arrayPointer();
    printf("%d", *ptr);
    return 0;
}*/
/*int* arrayPointer(){
     int array[5]={10,20,20,40,50};
    return &array[0];
}
int main()
{
    int *ptr = arrayPointer();
    printf("%d", *ptr);
    return 0;
}*/

/*int main() {
    int x = 7;
    
    
    printf("%d %d %d\n", x++, x++, ++x);
    return 0;
}*/

/*int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    (*ptr)++;
    printf("%d %d", *(ptr+2), *(arr+2));
    return 0;
}*/


 /*int main() {
    int arr[5] = {21, 35, 31, 43, 42};
    int i, *p = arr;
    for (i = 0; i < 5; i++) {
        
        (*p)--;
        printf("%d\n", *p++);
        
    }
    return 0;
}
*/
/*int power(int base, int exponent) {
    int result = 1;
    int i;
    
    for ( i = 1; i <= exponent; i++) {
        result *= base;
    }
    
    return result;
}

int main() {
    int base, exponent;
    
    printf("Enter base: ");
    scanf("%d", &base);
    
    printf("Enter exponent: ");
    scanf("%d", &exponent);
    
    printf("%d^%d = %d\n", base, exponent, power(base, exponent));
    
    return 0;
}*/

/*int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    a = a + b;
    b = a - b;
    a = a - b;

    printf("After swapping: a = %d, b = %d\n", a, b);

    return 0;
}*/

/*int main(){

    int i, num;
    int factorial =1;
    printf("Enter num:");
    scanf("%d",&num);

    for(i=num;i>=1;i--){
        factorial *= i;

    }
    printf("%d\n", factorial);


    return 0;
}*/