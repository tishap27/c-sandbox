#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data; 
    struct Node* next ;  
} Node;

void insertAtStart(Node** head, int data){
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->data = data; 
    
    if(*head == NULL){
        newNode->next = *head; 
        *head = newNode; 
        return; 
    }
    Node* temp = *head; 
    while(temp->next != *head){
        temp = temp->next;
    }
    newNode->next = *head; 
    temp->next =newNode; 
    *head = newNode ;

}

void insertAtEnd(Node** head, int data){
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->data = data; 

    if(*head ==NULL){
        newNode->next = newNode; 
        newNode = *head;
        return;
    }
    Node* temp = *head; 
    while(temp->next != *head){
        temp = temp->next;
    }
    temp->next = newNode; 
    newNode->next = *head; 
}

void deleteAtStart(Node** head){

    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* temp = *head;

    if (temp->next == *head) { 
        free(temp);
        *head = NULL;
        return;
    }

    Node* last = *head;
    while (last->next != *head)
        last = last->next;

    *head = (*head)->next;
    last->next = *head;

    free(temp);
}

void deleteAtEnd(Node** head){
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = *head;
    if(temp->next == *head){
        free(temp);
        *head = NULL; 
        return;
    }
    Node* prev = NULL; 
    while(temp->next != *head){
        prev = temp; 
        temp = temp->next;
    }
    prev->next = *head; 
    free(temp); 
}
int countNodes(Node* head){
    int count = 0;
    if(head == NULL){
        return 0 ; 
    }
    Node* temp = head; 
    do{
        count++;
        temp = temp->next; 
    }
    while(temp != head); 
    return count; 
}
int detectLoop(Node* head){
    if(head==NULL){
        printf("Empty list\n");
        return 0;
    }
    Node* slow = head; 
    Node* fast = head; 

    while(fast != NULL && fast->next != NULL){
        slow = slow->next; 
        fast = fast->next->next; 

        if(slow == fast){
            printf("Loop detected\n");
            return 1; 
        }
       
    }
        return 0;
}
void printList(Node* head){
    if(head == NULL){
        printf("Empty list\n");
        return;
    }
    Node* temp = head; 
    do{
        printf("%d->", temp->data); 
        temp = temp->next;
    } 
    while(temp != head);
    printf("Back to top\n");
}

int main(){
    Node* head = NULL; int i;
    for(i = 0 ; i<=3; i++){
        Node* newNode = (Node*)malloc (sizeof(Node));
        
        newNode->data = i* 10 ; 
        newNode->next = head;
        head = newNode ;
    }
    if(head !=NULL){
        Node* temp = head;

        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next=head; 
    }
    
    
    printf("Original List:\n"); 
    printList(head);

    printf("Insert At Start:\n");
    insertAtStart(&head, 40);
    printList(head);

    printf("Insert At End:\n");
    insertAtEnd(&head, 50);
    printList(head);

    printf("Delete At Start:\n");
    deleteAtStart(&head);
    printList(head);

    printf("Delete At End:\n");
    deleteAtEnd(&head);
    printList(head);
    
    printf("Number of nodes: %d \n", countNodes(head));
    printf("loop detected: %d\n ", detectLoop(head));

    return 0; 
}