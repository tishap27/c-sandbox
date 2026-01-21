/*#include <stdio.h>

void swap ( int *a , int *b ){
    int  t = *a ;
        *a = *b; 
        *b =  t; 

        printf("a : %d, b: %d\n", *a,*b);
}

int main(){
    int a = 3 ,  b = 5;

    swap(&a, &b);
    printf("a: %d, b: %d\n", a,b);

    return 0;

}*/




#include <stdio.h>

int main(){
    int mat1[2][2] , mat2[2][2], result[2][2];
    int i, j, k;

    printf("Enter mat1 elemnets");
    for(i=0;i<2; i++){
        for (j=0 ;j<2;j++){
            scanf("%d", &mat1[i][j]);

        }
    }
    printf("Enter mat2 elemnets");
    for(i=0;i<2; i++){
        for (j=0 ;j<2;j++){
            scanf("%d", &mat2[i][j]);

        }
    }



}











/*#include <stdio.h>

int main(){
    int num, i;
    printf("Enter num:");
    scanf("%d",&num);

        if(num < 1 ){
            printf("Invalid num");
        }
        else {
            for(i=2;i *i <num; i++){
                if (num % i ==0){
                    printf("Num is not prime\n");
                }else{printf("Num is prime\n");}
            }
        }
    return 0 ;
}*/







/*#include <stdio.h>

int main(){
    int coef[]={1,2,3,4};
    int x, result, i ;
    

    printf("Enter the value for x:");
    scanf("%d", &x);

    for(i=0;i<4;i++){
        result = result *x + coef[i];
    }

    printf("The solution is %d \n ", result);
    return 0;
}
*/





/*#include <stdio.h>

int main(){
    int i;
    for(i=1; i<=10 ; i++){
        printf("%d \t", i);
        if (i==5){
            break;
        }
    }
    printf("\n");

    return 0; 
}*/






/*#include <stdio.h>

int multiply(int a, int b ){

    return a * b ; 
}

int main(){
    int a , b, result;
    printf("enter num1:");
    scanf("%d", &a);
    printf("enter num2:");
    scanf("%d", &b);

    result = multiply(a,b);
    printf("Product is %d \n",result );
    return 0;
}*/






/*#include <stdio.h>

int main(){
    int arr[]={10,20,30,40,50};
    int i;
    

    for( i=0;i<5;i++){
        printf("%d \n", arr[i]);

    }

    return 0;
}
*/










/*#include <stdio.h>

int main(){
    int num ; 

    printf("Enter num:");
    scanf("%d",&num);

    if (num <0 ){
        printf("The number is negative");
    } 
    else if (num >0){
        printf("The number is positive");
    }
    else if (num == 0){
        printf("The number is zero");
    }

    return 0;
}
*/













/*#include <stdio.h>

int main(){
    int num1 = 7;
    int num2 = 7;
    int sum = num1 + num2 ;
    printf("The sum of %d + %d = %d \n", num1, num2, sum);

    return 0;
}*/





/*#include <stdio.h>

int main(){
    int a,b,c,d, det;

    printf("Enter 2*2 matrix elements: \n");

    printf("a:");
    scanf("%d", &a);
    printf("b:");
    scanf("%d", &b);
    printf("c:");
    scanf("%d", &c);
    printf("d:");
    scanf("%d", &d);

    det = (a*d)-(b*c);
    printf("The determinant of matrix is %d \n", det);

    
    


    return 0;
}*/