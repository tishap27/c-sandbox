#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; 
    struct Node* next;
} Node; 

void insertAtStart(Node** head, int data){
    Node* newNode = (Node*)malloc(sizeof(Node)); 
    
    newNode->data = data; 
    newNode->next = *head; 
    *head =  newNode; 
}

void insertAtEnd(Node** head, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data; 
        newNode->next = NULL; 

        if (*head == NULL) {
            *head = newNode;
            return;
        }

        Node* temp = *head; 

        while(temp->next != NULL){
            temp = temp ->next; 
        }
        temp ->next = newNode; 
}

void deleteAtStart(Node** head){
    if (*head == NULL){
        printf("Empty list"); 
        return; 
    }
    Node* temp =*head; 
    *head = (*head)->next ; 
    free(temp);
}

void deleteAtEnd(Node** head){
    if(*head ==NULL){
        printf("Empty list\n");
        return;
    }
    if((*head)->next ==NULL){
        free(*head); 
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while(temp->next->next != NULL){
        temp = temp->next; 
    }
    free(temp->next); 
    temp->next =NULL;

}

void reverseList(Node** head){
    Node* prev = NULL;
    Node* next = NULL;
    Node* current = *head ;  

    while(current != NULL){
        next = current->next ; 
        current->next = prev; 
        prev = current ; 
        current = next; 
    }
    *head = prev ; 

}
Node* findNode(Node* head , int value){
    while(head != NULL){
        if(head->data = value){
            return head;
        }
    }
    return NULL; 
}

void printList(Node* head){
    
    while(head != NULL){
        printf("%d-> ", head->data);
        head = head->next; 
    }
    printf("\n") ; 
}

int main(){
    Node* head = NULL; 
    Node* newNode = NULL; Node* result = NULL; 
    int i ; 

    for ( i = 0 ; i<= 3 ; i++){
     Node* newNode = (Node*)malloc(sizeof(Node));  

     newNode->data = i * 10 ; 
     newNode-> next = head ; 
     head = newNode; 
    }
    printf("Original list:\n");
    printList(head);

    insertAtStart(&head , 40); 
    printf("Insert At Start:\n");
    printList(head);

    insertAtEnd(&head , 50); 
    printf("Insert At End:\n");
    printList(head);

    deleteAtStart(&head); 
    printf("Delete At Start:\n");
    printList(head);

    deleteAtEnd(&head); 
    printf("Delete At End:\n");
    printList(head);

    reverseList(&head); 
    printf("Reversed List:\n");
    printList(head);

    result = findNode(head, 20); 
    if(result){
        printf("Node found at %p\n", (void*)result);
    } 
    else {
        printf("Node not found\n");
    }

    return 0;
}