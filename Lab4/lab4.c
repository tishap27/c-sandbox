/* 
============================================================================ 
Name        : main.c 
Author      : <<< Tisha Patel (pate1416) >>> 
Version     : Lab 4 
Description : structs in C, Ansi-style 
Status      
 
Builds clean; no warning(s)                    : << true >>               
Requirement #1 - struct Student                : << complete >>               
Requirement #2 - struct Course                 : << complete >>              
Requirement #3 - typedef Course struct         : << complete >>        
Requirement #4 - Prompt for number of students : << complete >>  
Requirement #5 - Prompt for student information: << complete >> 
Requirement #6 - Prompt for course information : << complete >> 
Requirement #7 - Display registration          : << complete >> 
: << complete xor not complete >> 
============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN_STUDENT 1
#define MAX_NAME_LENGTH 20
#define STUDENT_ID_LENGTH 5
#define MIN_STUDENT_ID 10000
#define MAX_STUDENT_ID 99999
#define COURSE_CODE_LENGTH 7
#define MAX_COURSE_CODE_LENGTH 8
#define MAX_COURSE_NAME_LENGTH 25
#define VALID 1
#define INVALID 0



typedef struct {
    char courseCode[MAX_COURSE_CODE_LENGTH];
    char courseName[MAX_COURSE_NAME_LENGTH];
} Course;

typedef struct {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int studentID;
    Course *course;
} Student;

int isValidStudentID(int id) {
    return (id >= MIN_STUDENT_ID && id <= MAX_STUDENT_ID);
}

int isValidCourseCode(const char *code) {
    int i;
    if (strlen(code) != COURSE_CODE_LENGTH) return INVALID;
    for (i = 0; i < COURSE_CODE_LENGTH; i++) {
        if (!isalnum(code[i])) return INVALID;
    }
    return VALID;
}

void getStudentInfo(Student *student, int studentNumber) {
    
    printf("Enter student #%d First Name: ", studentNumber);
    scanf("%19s", student->firstName);
    
    printf("Enter student Last Name: ");
    scanf("%19s", student->lastName);
    
    do {
        printf("Enter student ID: ");
        if (scanf("%d", &student->studentID) != 1) {
            /* Clear input buffer if invalid input */
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        if (!isValidStudentID(student->studentID)) {
            printf("Invalid student ID. Please enter a 5-digit number.\n");
        }
    } while (!isValidStudentID(student->studentID));
   

    while (getchar() != '\n');
}

void getCourseInfo(Course *course) {
    do {
        printf("Enter course code: ");
        scanf("%7s", course->courseCode);
        if (!isValidCourseCode(course->courseCode)) {
            printf("Invalid course code. Please enter 7 alphanumeric characters.\n");
        }
    } while (!isValidCourseCode(course->courseCode));

    printf("Enter course name: ");
    getchar(); 
    fgets(course->courseName, sizeof(course->courseName), stdin);
    course->courseName[strcspn(course->courseName, "\n")] = 0; 
}

void displayInfo(Student *students, int numStudents) {
    int i;
    printf("\n");
   
    for (i = 0; i < numStudents; i++) {
        printf("\n");
        
        printf("Student Name: %s %s\n", students[i].firstName, students[i].lastName);
        printf("Student ID: %05d\n", students[i].studentID);
        printf("Course Code: %s\n", students[i].course->courseCode);
        printf("Course Name: %s\n", students[i].course->courseName);
        printf("\n");
    }
}

int main() {
    int numStudents;
    int i, j;
    Student *students;

    printf("How many students do you wish to enter = ");
    if (scanf("%d", &numStudents) != 1 || numStudents < MIN_STUDENT) {
        printf("Invalid input for number of students.\n");
        return EXIT_FAILURE;
    }
    
    while (getchar() != '\n');

    students = (Student *)malloc(numStudents * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < numStudents; i++) {
        getStudentInfo(&students[i], i + 1);
        
        students[i].course = (Course *)malloc(sizeof(Course));
        if (students[i].course == NULL) {
            printf("Memory allocation failed for course.\n");
            /* Free previously allocated memory */
            for (j = 0; j < i; j++) {
                free(students[j].course);
            }
            free(students);
            return EXIT_FAILURE;
        }
        getCourseInfo(students[i].course);
    }

    displayInfo(students, numStudents);

    
    for (i = 0; i < numStudents; i++) {
        free(students[i].course);
    }
    free(students);

    return EXIT_SUCCESS;
}