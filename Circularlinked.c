/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DNode{
   char name[50];
   struct DNode *prev; 
   struct DNode *next; 
}DNode;

DNode* createList(char const *name){
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if(newNode == NULL){
        return 1;
    }

    strcpy(newNode->name , name);
    newNode->prev = NULL; 
    newNode->next = NULL; 
    return newNode; 
}
DNode* circularList(){
    DNode *head = NULL, *temp = NULL , *newNode =NULL; 
    int i ; 
    const char *names[]= {"Alice", "Will", "Bob", "JOhn", "Eve", "Marie"};

    for(i = 0; i <6; i++){
        newNode = createList(names[i]);
        if(head == NULL){
            head = newNode;
        }else{
            temp->next = newNode; 
            newNode->prev = temp; 
        }
        temp=newNode; 
    }
    head->prev = temp;
    temp->next = head; 
    return head;
}

int countNodes(DNode* head){
    if(head== NULL){
        return 0 ; 
    }
    int count = 0;
    DNode* temp = head; 

    do{
        count++;
        temp =temp->next; 
    }
    while(temp != head); 
    return count; 
}
void reverseSecondHalf(DNode* head) {
    if (!head || !head->next) return;

    // Find middle node
    DNode *slow = head, *fast = head;
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split list into two halves
    DNode *firstTail = slow;         // Last node of the first half
    DNode *secondHead = slow->next;  // First node of the second half
    DNode *lastNode = head->prev;    // Last node of the entire list

    // Break circular links temporarily
    firstTail->next = NULL;
    lastNode->next = NULL;
    secondHead->prev = NULL;

    // Reverse the second half
    DNode *current = secondHead, *temp = NULL, *newSecondHead = NULL;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        newSecondHead = current;  // Update new head of reversed second half
        current = current->prev;
    }

    // Reconnect the reversed second half to the first half and make it circular again
    firstTail->next = newSecondHead;
    newSecondHead->prev = firstTail;

    lastNode->next = head;
    head->prev = lastNode;
}
void printList(DNode* head){
    if(head == NULL){
        return;
    }
    DNode* temp = head; 

    do{
        printf("%s : \n", temp->name);
        temp= temp->next; 
    }
    while(temp != head);
    printf("Back to start \n");
}

int main(){
    DNode* head = circularList();
    printf("The list is: \n"); 
    printList(head);

    int totalCount = countNodes(head); 
    printf("The count is %d\n", totalCount);

    reverseSecondHalf(head);
    
    printf("\nAfter Reversing Second Half:\n");
    printList(head);

    return 0;
}

*/



















/*SINGLY CIRCULAR LIST*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char name[50];
    struct Node* next ;
}Node;

Node* createList(const char* name){
    Node* newNode = (Node*)malloc(sizeof(Node));

    if(newNode == NULL ){
        printf("Memory allocation failed \n");
        return 1;
    }
    strcpy(newNode->name , name);
    newNode->next = NULL;
    return newNode;
}

Node* circularList(){
    Node *head = NULL, *temp = NULL, *newNode =NULL;
    int i; 
    const char* names[]= {"Alice", "John", "Bob", "Marie", "Will", "Eve"};
    
    for(i= 0 ; i<6 ; i++){

        newNode = createList(names[i]);
        if(head ==NULL){
            head = newNode;
        }else{
            temp->next = newNode;
        }
        temp = newNode ;
    }
    temp->next = head; 
    return head; 

}

void printList(Node* head){
    if(head == NULL){
        return 1;
    }

    Node *temp = head; 
    do{
        printf("%s:", temp->name);
        temp = temp->next;

    }while(temp !=head);
    printf("Back to start\n");
}
void reverseSecondHalfCircular(Node* head) {
    if (!head || !head->next || !head->next->next) return;

    
    Node *slow = head, *fast = head;
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *prev = NULL, *current = slow->next, *next = NULL, *tail = slow;

    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != head);

    tail->next->next = head; 
    tail->next = prev;      
}

int main(){
    Node *head = circularList();
    printf("Circular list is - \n");
    printList(head);

    reverseSecondHalfCircular(head);

    printf("\nAfter Reversing Second Half:\n");
    printList(head);
    
    return 0;
}