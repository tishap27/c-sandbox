#ifndef NODE_H
#define NODE_H

#define NUM_STUDENTS 3    /*NUMBER OF STUDENTS GIVEN AS PER ASSIGNMENT REQUIREMENTS*/
#define MAX_NAME_LENGTH 19

/* Define student structure (student_t) */
typedef struct {
    char first_name[20];
    char last_name[20];
} student_t;

/* Define node structure (node_t) */
typedef struct Node {
    student_t *student;  /* Pointer to student structure */
    struct Node *next;   /* Pointer to the next node in the list */
} node_t;

/* Function Prototypes */
void addStudentAtBeginning(node_t **head, student_t *student);
void addStudentAtEnd(node_t **head, student_t *student);
void deleteFirstStudents(node_t **head, int count);
void deleteLastStudents(node_t **head, int count);
void deleteSecondStudent(node_t **head);
void printList(node_t *head);
student_t *createStudent(const char *first_name, const char *last_name);
void freeList(node_t *head);

#endif  /*NODE_H*/