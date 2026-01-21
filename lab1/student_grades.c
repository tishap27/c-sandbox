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



int main() {
    int numStudents, i, grade;
    char name[Max_NAME_LENGTH];
    


/*Number of students*/
    printf("Enter the number of students (min %d to max %d): ",MIN_STUDENTS, MAX_STUDENTS);
    scanf("%d", &numStudents);

    if (numStudents < MIN_STUDENTS || numStudents > MAX_STUDENTS) {
        printf("Invalid number of students. Please enter a number between %d and %d.\n", MIN_STUDENTS, MAX_STUDENTS);
        return EXIT_FAILURE;
    }
      /* loop through each student*/
    for (i = 1; i <= numStudents; i++) {
       

        printf("\nEnter name for student %d: ", i);
        scanf("%s", name);

          /*name should be only in alphabets*/
        if (!isalpha(name[0])){
            printf("Invalid name. Enter alphabetic characters. \n ");

            i--;
            continue;
        } 
        

        /*student grade*/
        printf("Enter grade for %s: ", name);
        scanf("%d", &grade);

        if (grade < MIN_GRADE || grade > MAX_GRADE) {
            printf("Invalid grade. Please enter a grade between 0 and 100.\n");
            i--;
            continue;
        }

        #if PASSING_GRADE > MIN_GRADE
        if (grade >= PASSING_GRADE) {
            printf("%s has passed.\n", name);
        } else {
            printf("%s has failed.\n", name);
        }
        #else
        #error "PASSING_GRADE must be greater than 0"
        #endif
    }

    return EXIT_SUCCESS;
}
