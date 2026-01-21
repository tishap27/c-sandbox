#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

int main() {
    node_t* head = NULL;
    int i;
    char first_name[20], last_name[20];

    printf("Linked List of Students\n");

    /* Add 3 students to the beginning of the list */
    for(i=1; i<=NUM_STUDENTS; i++){
        printf("Enter first name for student %d: ", i);
        scanf("%19s", first_name);

        printf("Enter last name for student %d: ", i);
        scanf("%19s", last_name);

        addStudentAtBeginning(&head, createStudent(first_name, last_name));
    }
	 printf("\n");
    /* Add 3 students to the end of the list */
    for(i=1; i<=NUM_STUDENTS; i++){
        printf("Enter first name for student %d: ", i); 
        scanf("%19s", first_name);

        printf("Enter last name for student %d: ", i); 
        scanf("%19s", last_name);

        addStudentAtEnd(&head, createStudent(first_name, last_name));
    }

    printf("\nCurrent list of students:\n");
    printList(head);

    /* Delete the first 3 students from the list */
    deleteFirstStudents(&head, 3);

    printf("\nAfter deleting the first 3 students:\n");
    printList(head);

    /* Delete the last 3 students from the list */
    deleteLastStudents(&head, 3);

    printf("\nAfter deleting the last 3 students:\n");
    printf("\nFinal list of students:\n");
    printList(head);

    /* Re-add 3 students to the end of the list */
    for(i=1; i<=3; i++){
        printf("Enter first name for student %d: ", i); 
        scanf("%19s", first_name);

        printf("Enter last name for student %d: ", i); 
        scanf("%19s", last_name);

        addStudentAtEnd(&head, createStudent(first_name, last_name));
    }

    /* Delete the second student from the list */
    deleteSecondStudent(&head);

    printf("\nAfter deleting the second student:\n");
    printList(head);

    freeList(head);

    return EXIT_SUCCESS;
}