#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

student_t *createStudent(const char *first_name, const char *last_name) {
    student_t *new_student = (student_t *)malloc(sizeof(student_t));
    if (new_student == NULL) {
        fprintf(stderr, "Memory allocation failed for new student.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(new_student->first_name, first_name, 19);
    new_student->first_name[MAX_NAME_LENGTH] = '\0';
    strncpy(new_student->last_name, last_name, 19);
    new_student->last_name[MAX_NAME_LENGTH] = '\0';
    return new_student;
}

void addStudentAtBeginning(node_t **head, student_t *student) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->student = student;
    new_node->next = *head;
    *head = new_node;
}

void addStudentAtEnd(node_t **head, student_t *student) {
    node_t *new_node;
    node_t *current;

    new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->student = student;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void deleteFirstStudents(node_t **head, int count) {
    int i;
    
    for (i = 0; i < count && *head != NULL; i++) {
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp->student);
        free(temp);
    }
}

void deleteLastStudents(node_t **head, int count) {
    int total_nodes = 0;
    int i;
    node_t *current;
    node_t *temp;

    if (*head == NULL) return;

    current = *head;
    
    while (current != NULL) {
        total_nodes++;
        current = current->next;
    }

    if (count >= total_nodes) {
        freeList(*head);
        *head = NULL;
        return;
    }

    current = *head;

    for (i = 0; i < total_nodes - count - 1; i++) {
        current = current->next;
    }

    temp = current->next;    
    current->next = NULL;

    while (temp != NULL) {
        node_t *to_delete = temp;
        temp = temp->next;
        free(to_delete->student);
        free(to_delete);
    }
}

void deleteSecondStudent(node_t **head) {
   node_t *second_node;

   if (*head == NULL || (*head)->next == NULL)
   return;

   second_node = (*head)->next;

   (*head)->next = second_node->next;

   free(second_node->student);
   free(second_node);
}

void printList(node_t *head) {
   node_t *current;

   current = head;

   while (current != NULL) {
       printf("Student: %s %s\n", current->student->first_name, current->student->last_name);
       current = current->next;
   }
}

void freeList(node_t *head) {
   node_t* temp;

   while (head != NULL) {
       temp = head;
       head = head->next;

       free(temp->student);
       free(temp);
   }
}