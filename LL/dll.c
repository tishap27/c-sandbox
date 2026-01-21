#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data; 
    struct Node* next ; 
    struct Node* prev; 
} Node; 

void insertAtStart(Node** head, int data){
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->data = data;
    newNode->next = *head; 
    newNode->prev = NULL ;
    if(*head != NULL){
        (*head)->prev = newNode; 
    }
    *head = newNode; 

}

void InsertAtEnd(Node** head, int data){
    Node* newNode = (Node*)malloc (sizeof(Node));
    newNode->data = data ; 
    newNode->next = NULL; 
    
    if(*head == NULL){
        newNode->prev = NULL ; 
        *head = newNode; 
    }
    Node* temp = *head; 
    while(temp ->next != NULL){
        temp= temp->next; 
    }
    temp->next = newNode;
    newNode->prev = temp; 
}
void deleteAtStart(Node** head){
    if(*head == NULL){
        printf("Empty list\n");
        return;
    }
    Node* temp = *head; 
    *head = (*head)->next; 

    if(*head != NULL){
        (*head)->prev = NULL; 
   }
   free(temp); 
}
void deleteAtEnd(Node** head){
    if(*head == NULL){
        printf("eMPTY LIST\n"); 
        return;
    }
    Node* temp = *head;
    while(temp->next == NULL){
        free(temp); 
        *head =NULL; 
        return; 
    } 
    while(temp->next != NULL){
        temp = temp ->next; 
    }
    temp->prev->next = NULL; 
    free(temp); 
}

void deleteSpecificNode(Node** head, Node* del){
    if(*head == NULL || del == NULL){
        return;
    }
    if(*head == del){
        *head = del->next; 
    }

    if(del->next !=NULL){
        del->next->prev = del->prev; 

    }
    if(del->prev !=NULL){
        del->prev->next = del->next ; 
    }
    free(del);

}

void traverseFromStart(Node* head){
    printf("   List from start:\n");
    while(head != NULL){
        printf("%d->", head->data);
        head = head->next;
    }
    printf("\n");
}

void traverseFromEnd(Node* head){
    if (head == NULL)
        return;

    while(head->next != NULL)
        head= head->next;
    
    printf("List from end:\n"); 

         printf("%d->", head->data);
         head = head->prev; 
    
    printf("\n");
}

void printList(Node* head){
    Node* temp = head ; 
    do{
        printf("%d->", temp->data); 
        temp = temp->next; 
    }
    while(temp != NULL); 
    printf("\n"); 
}

int main(){
Node* head = NULL; int i;
Node*second = NULL; 
for(i = 0 ; i<=3; i++){
    Node* newNode = (Node*)malloc (sizeof(Node));

    newNode->data = i* 10 ; 
    newNode->next = head;
    head = newNode ;
}
    printf("Original List:\n"); 
    printList(head);

    printf("Insert At Start:\n"); 
    insertAtStart(&head, 40);
    printList(head);

    printf("Insert At End:\n"); 
    InsertAtEnd(&head, 50);
    printList(head);

    printf("Delete At Start:\n"); 
    deleteAtStart(&head);
    printList(head);

    printf("Delete At End:\n"); 
    deleteAtEnd(&head);
    printList(head);

    printf("Traverse from start:\n"); 
    traverseFromStart(head);
    //printList(head);

    printf("Traverse from End:\n"); 
    traverseFromEnd(head);

    printf("Deleting Specific Node:\n"); 
    second->prev = head; 
    deleteSpecificNode(&head, second);
    printList(head);

    return 0; 
}