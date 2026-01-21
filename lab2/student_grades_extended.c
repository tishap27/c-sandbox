#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*constants parameters to minimize magic numbers */
#define MAX_STUDENTS 100
#define PASSING_GRADE 60
#define MIN_STUDENTS 1
#define MIN_GRADE 0
#define MAX_GRADE 100
#define Max_NAME_LENGTH 50
#define GRADE_COUNT 3

/*Formula for average grade calculation*/
float calculate_average(int *grade, int count) {
    int i, sum = 0;
    for (i = 0; i < count; i++) {
        sum += grade[i];
    }
    return (float)sum / count;
} 


int main (){
int numStudents, i , j;
int *grade;
char *name ;
float *average;

    

printf("Enter the number of students (min %d to max %d): ",MIN_STUDENTS, MAX_STUDENTS);
scanf( "%d" , &numStudents);

if(numStudents<MIN_STUDENTS || numStudents > MAX_STUDENTS){
    printf("Invalid number of students. Please enter a number between %d and %d.\n", MIN_STUDENTS, MAX_STUDENTS);
    return EXIT_FAILURE;
}

     name = malloc(numStudents * Max_NAME_LENGTH * sizeof(*name));
     grade = malloc(numStudents * GRADE_COUNT * sizeof(*grade));
     average = malloc(numStudents * sizeof(*average));

     if (name == NULL || grade == NULL || average == NULL) {
        printf("Memory allocation failed.\n");
        free(name);
        free(grade);
        free(average);
        return EXIT_FAILURE;
    }


for(i=0; i<numStudents; i++){   
    printf("\nEnter name for student %d: ", i + 1);
    scanf("%s" , &name[i * Max_NAME_LENGTH]);
        /*name should be only in alphabets*/
        if (!isalpha(name[i * Max_NAME_LENGTH])){
            printf("Invalid name. Enter alphabetic characters. \n ");

            i--;
            continue;
        }

        for (j=0 ; j< GRADE_COUNT; j++){
            printf("Enter grade %d for %s(0-100): ",j+1 ,  &name[i* Max_NAME_LENGTH]);
        scanf("%d", &grade[i * GRADE_COUNT +j]);
        

        if (grade[i*GRADE_COUNT + j] < MIN_GRADE || grade[i*GRADE_COUNT + j] > MAX_GRADE) {
            printf("Invalid grade. Please enter a grade between 0 and 100.\n");
            j--;
            continue;

        }
        
            }  
            average[i]= calculate_average(&grade[i * GRADE_COUNT], GRADE_COUNT);  }

            
    

       printf("\nStudent Grades:\n");
for (i = 0; i < numStudents; i++) {
    const char* status;
    if (average[i] >= PASSING_GRADE) {
        status = "Pass";
    } else {
        status = "Fail";
    }
    
    printf("%s: Average = %.1f, Status: %s\n",
           &name[i * Max_NAME_LENGTH], average[i], status);
}
free(name);
free(grade);
free(average);
    

    return EXIT_SUCCESS;
}







