/*number greater than 9 and less than 100*/
/*if student passedd or failed  */
/*grade students <30 C ,30-70 B,  70-=90 A, 90-100 A+*/
/*if character is upper case or not */
/*print number 0 to n if n is given by user */
/*for , while and fo while loop*/
/*print sum of first n natural numbers and print sequence in reverse*/
/*prnt  table of numebr inputted by user*/
/*ask input until user enters odd number*/
/*ask input until user enters multiple of seven*/
/*print all numbers 1 to 10 expcept 6*/
/*print all te odd numbers 5 to 50 */
/*print factorial of number n */
/*print reverse table for number given by user*/
/*calculate sum of all numbers betwenn 5 and 50*/
/*function declraion, protoype and call */
/*write function that prints namaste if user is indian and bonjour if user is french*/
/*add to numbers via function*/ /*function that prints table n */
/*add gst of 18% use function*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int i , j=20;
    for(i=1;i<=j;i++){
        printf("%d \n",i);
        j--;
    }


    exit (EXIT_SUCCESS);
}
/*int main(){
    
    float final;  
    
    final = pow (4 , 2 );
    printf("%f", final);
    return 0;
}*/




/*void printPrice(float value){
    float v;
    v =value +(value*0.18);
    printf("The final price is %2f", v);
}

int main(){
    float num; 

    printf("Enter the ACTUAL price: ");
    scanf("%f", &num);

    printPrice(num);
    return 0;

}*/

























/*#include <stdio.h>

int sum(int x, int y ){  
    return x+y; 
}

void Table(int z){
    int i ; 
    for(i=1; i<=10;i++){
        
        printf("%d \n", z*i);
    }

}

int main(){
    int num1; 
    int num2; 
    int num3;
    int addition;

    printf("Enter num1:");
    scanf("%d", &num1);

    printf("Enter num2:");
    scanf("%d", &num2);

    addition = sum(num1, num2);
    printf("The sum is %d \n" , addition);

    printf("Enter num for table:");
    scanf("%d", &num3);
    printf("The table is:\n");
    Table(num3);
    return 0; 



}*/