#include <stdio.h>
#include <stdlib.h>
typedef struct student{
    char name[50]; 
    int rollNo; 
    float marks[5]; 
}student;
int main(){
    int num, i , j; 

    printf("Enter num of students:"); 
    scanf("%d", &num); 
    
    student students[num]; 

    for(i = 0 ; i <num ; i++){
        printf("Enter student details %d:\n", i+1);
        
        printf("Name: ");
        scanf("%s", students[i].name); 
        printf("RollNo:"); 
        scanf("%d", &students[i].rollNo); 
        printf("Enter 5 subject marks:");
        for(j = 0  ; j <5; j++){
            scanf("%f", &students[i].marks[j]);
        }
    }
    //print details
    for(i = 0 ; i< num; i ++){
        printf("Name : %s\t rollNo: %d\t", students[i].name, students[i].rollNo);
        for(j= 0; j<5; j++){
            printf("%.2f", students[i].marks[j]);
        }
        printf("\n"); 
    }

    return 0; 
}