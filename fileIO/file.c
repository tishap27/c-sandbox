/*Read 5 int from file test.txt(i also wrote it from c )*/
/*input student info from user and store into file*/
/*print all odd number from 1 to n in a file*/
/*2 numbers are given in a file read thode numbers than print sum of numbers in the file*/

#include <stdio.h>

int main(){
int a , b;
FILE *fptr ; 
fptr = fopen("sum.txt", "r");

fscanf(fptr, "%d", &a);
fscanf(fptr, "%d", &b);

fclose(fptr);

fptr = fopen("sum.txt", "a");

fprintf(fptr, "\nThe sum is %d", a + b);
fclose(fptr);
    return 0; 
}










/*#include <stdio.h>

int main(){
    int i, n;
    FILE *fptr ;
    fptr = fopen("odd.txt", "w");

    printf("Enter n: ");
    scanf("%d", &n);
    fprintf(fptr, "List of odd number till %d are: \n", n);
    for(i=1; i<=n ; i++){
        if(i % 2 != 0){
        fprintf(fptr, "%d\t", i);
        }
    }
    fclose(fptr);
    return 0 ;
}*/














/*int main(){
    char name[50];
    int age; 
    float cgpa;
    FILE *fptr ;
    fptr = fopen("student.txt", "w");

    printf("Enter name:");
    scanf("%s", name);
    printf("Enter age:");
    scanf("%d", &age);
    printf("Enter cgpa:");
    scanf("%f", &cgpa);

    fprintf(fptr , "Student name: %s\n", name);
    fprintf(fptr, "Student age: %d\n", age);
    fprintf(fptr, "Student cgpa: %.2f", cgpa);

    fclose(fptr);


    return 0;
}*/

















/*#include <stdio.h>

int main(){
    int n;
    FILE *fptr;
    fptr = fopen("test.txt", "w");

    fprintf(fptr, "%d\t", 1);
    fprintf(fptr, "%d\t", 2);
    fprintf(fptr, "%d\t", 3);
    fprintf(fptr, "%d\t", 4);
    fprintf(fptr, "%d", 5);

    fclose(fptr);
    
    fptr = fopen("test.txt", "r");

    fscanf(fptr , "%d", &n);
    printf("number: %d\n", n);
    fscanf(fptr,"%d" , &n);
    printf("number: %d\n", n);
    fscanf(fptr,"%d" , &n);
    printf("number: %d\n", n);
    fscanf(fptr,"%d" , &n);
    printf("number: %d\n", n);
    fscanf(fptr,"%d" , &n);
    printf("number: %d\n", n);
    
    
    
    fclose(fptr);
    
    
    return 0 ;
}*/










/*int main(){
    char ch;
    FILE *fptr;
    fptr = fopen("text.txt", "r");

    ch= fgetc(fptr);
    while(ch!= EOF){
        printf("%c", ch);
        ch = fgetc(fptr);
    }

    printf("\n");
    fclose(fptr);

    return 0;

}
*/







/*int main(){
    
    FILE *fptr ;
    fptr = fopen("text.txt", "a");
    
    fprintf(fptr , "%c", 'A');
    fprintf(fptr , "%c", 'P');
    fprintf(fptr , "%c", 'P');
    fprintf(fptr , "%c", 'L');
    fprintf(fptr , "%c", 'E');*/

    /*printf("%c\n", fgetc(fptr));
    printf("%c\n", fgetc(fptr));
    printf("%c\n", fgetc(fptr));
    printf("%c\n", fgetc(fptr));

    fputc('A', fptr);
    fputc('P', fptr);
    fputc('P', fptr);
    fputc('L', fptr);
    fputc('E', fptr);
    

    fclose(fptr);

    return 0;
}*/

















/*int main()
{
    char ch;
    FILE *fptr;
    fptr = fopen("text.txt", "r");

    fscanf(fptr, "%c", &ch);
    printf("character: %c\n", ch);

    fclose(fptr);
    return 0;
}*/

/*int main(){

    FILE *fptr;
    fptr = fopen("Newtext.txt", "w");
    if (fptr == NULL){
        printf("File doesn't exist\n");
    }else{
        fclose(fptr);
    }

    return 0;
}*/