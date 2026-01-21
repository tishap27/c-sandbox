#include <stdio.h>

int main(){

    int arr[]= { 1, 2, 3 ,4,5}; 
     
    printf("%d \n", arr[4]);

    printf("%p \n", &arr[0]);
    printf("%p \n ", arr);
    printf("%p \n", &arr[1]);
    printf("%p \n",&arr[2]);

    return 0; 
}


 /*BASIC OF PTR*/
/*int main(){

        int a = 7; 
        int *ptr = &a ; 
        int *ptr2 =NULL;; 

        printf("Value of *ptr: %d\n", *ptr);

        printf("Address of &a: %p\n", &a);

        printf("Address stored in *ptr : %p\n", ptr);

        printf("Address stored of *ptr : %p\n", &ptr);

        printf ("Address of some garbage value is: %p\n", ptr2);  //when ptr2 is not initialized to NULL it ahs some garbage value

        printf ("Address of some garbage value is: %p\n", ptr2); //whne initialized to null makes sure its empty

    return 0 ; 

}*/