#include <stdio.h>
#include <stdlib.h>

struct node{
    int data; 
    struct node *next ; 

};

void traverse (struct node *ptr){
    while(ptr!= NULL){
        printf("%d \t", ptr->data);
        ptr = ptr->next;
    }
}
struct node* insertAtFirst(struct node *head , int data){
    struct node *ptr = (struct node*)malloc (sizeof(struct node));
    
    ptr->next = head ; 
    ptr->data = data; 
    return ptr; 
}
struct node* insertAtBetween_Index(struct node *head , int data , int index){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    struct node *p = head ; 
    int i =0 ; 

    while(i != index -1){
        p = p->next ; 
        i++;
    }
    ptr->data = data; 
    ptr->next =p->next; 
    p->next = ptr; 
    return head; 
}
struct node* insertAtEnd(struct node *head, int data){
    struct node *ptr = (struct node*)malloc (sizeof(struct node));
    struct node *p = head; 
    ptr->data = data ; 

    while (p->next != NULL){
        p= p->next ; 
    }
    p->next= ptr; 
    ptr->next = NULL;
    
    return head; 

}
struct node* insertAfterNode(struct node*head , int data, struct node* givenNode){

    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data; 

    ptr->next = givenNode->next; 
    givenNode->next = ptr;

    return head; 

} 
int main(){
struct node *head; 
struct node *second; 
struct node *third;  
struct node *fourth;
head = (struct node*)malloc (sizeof(struct node));
second = (struct node*)malloc (sizeof(struct node));
third = (struct node*)malloc (sizeof(struct node));
fourth = (struct node*)malloc (sizeof(struct node));


head->data = 7;
head->next = second; 
second->data =8;
second->next = third;
third->data =9 ; 
third->next = fourth; 
fourth->data =10;
fourth->next=NULL;

traverse(head);
/*head = insertAtFirst(head , 1);
printf("New list insert at first");
traverse(head);*/

/*head = insertAtBetween_Index(head , 1 , 2);
printf("New list\n");
traverse(head);*/

/*head = insertAtEnd(head, 1);
printf("New list \n");
traverse(head);*/

head = insertAfterNode(head , 1 , third);
printf("Newlist\n");
traverse(head);
    return 0;
}





/*#include <stdio.h>
#include <stdlib.h>

struct node{
    int data; 
    struct node *next ; 

};

void traverse (struct node *ptr){
    while(ptr!= NULL){
        printf("%d \t", ptr->data);
        ptr = ptr->next;
    }
}

int main(){
struct node *head; 
struct node *second; 
struct node *third;  
head = (struct node*)malloc (sizeof(struct node));
second = (struct node*)malloc (sizeof(struct node));
third = (struct node*)malloc (sizeof(struct node));

head->data = 7;
head->next = second; 
second->data =8;
second->next = third;
third->data =9 ; 
third->next = NULL; 

traverse(head);
    return 0;
}
*/
