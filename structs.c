

/*make norma struct*/
/*arrays of structures*/
/*pointers to structures */
/*passing structures to functions*/
/*store adress(UnitNumber(int), blockno, city, state) of 5 people*/
/*call by ref*/

#include <stdio.h>
#include <string.h>

struct student{
    char name[50];
    int roll;
};

void getInfo(char* name, int* roll){
    
    /*strcpy(name, "John");
    *roll=27;*/
    /*scanf("%49s %d", name, roll);*/
    /*the above doesnt let me enter JOHN DOE hence we need to use fgets*/
    printf("Enter name:");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter roll:"); 
    scanf("%d" , roll);
    getchar();
}

int main(){
    struct student s1; 
    getInfo(s1.name, &s1.roll);
    printf("name: %s\nroll: %d\n", s1.name, s1.roll);

    return 0; 
}












/*#include <stdio.h>
#include <string.h>

 struct address{
    int UnitNum;
    int blockNum; 
    char city[100];
    char state[10];
} ; 
void printInfo( struct address add){

    printf("printed info: %d, %d, %s, %s\n", add.UnitNum, add.blockNum, add.city, add.state);

}
int main(){

    struct address add[5];
    printf("Enter details person1:");
    scanf("%d", &add[0].UnitNum);
    scanf("%d", &add[0].blockNum);
    scanf("%s", add[0].city);
    scanf("%s", add[0].state);

    printf("Enter details person2:");
    scanf("%d", &add[1].UnitNum);
    scanf("%d", &add[1].blockNum);
    scanf("%s", add[1].city);
    scanf("%s", add[1].state);

    printInfo(add[0]);
    printInfo(add[1]);

     return 0; 


   //printf("person1\n: %d, %d, %s, %s\n", addresses[0].UnitNum, addresses[0].blockNum, addresses[0].city, addresses[0].state);
   // printf("person2\n: %d, %d, %s, %s\n", addresses[1].UnitNum, addresses[1].blockNum, addresses[1].city, addresses[1].state);
    

   
}*/


/*#include <stdio.h>
#include <string.h>

struct student {
    int rollNo;
    float cgpa;
    char name[100];
};

void printInfo(struct student s1){
    printf("student rollno : %d\n", s1.rollNo);
    printf("student cgpa: %f\n", s1.cgpa);
    printf("student name %s\n",s1.name);
}

int main(){
    struct student s1 = {37, 9.2, "John"};
    printInfo(s1);

    return 0;
}*/

/*struct student {
    int rollNo;
    float cgpa;
    char name[100];
};

int main(){
    struct student s1= {37, 9.2, "John"}; 
    struct student *ptr; 
    ptr = &s1; 

    printf("student data with dot operator : %d\n ", (*ptr).rollNo);
    printf("student->roll with arrow operator : %d\n", ptr->rollNo);
    printf ("student name %s",ptr->name);
    return 0 ; 
}
*/

/*struct student {
    int rollNo;
    float cgpa;
    char name[100];
};


int main(){
    struct student IT[50];
    IT[0].rollNo = 35;
    IT[0].cgpa = 9.2;
    strcpy(IT[0].name , "john");
    
    printf("Student data: \n");
    printf("name %s\n roll no %d \n cgpa %f\n", IT[0].name, IT[0].rollNo, IT[0].cgpa);

    return 0;
}*/










/*struct student {
    int rollNo;
    float cgpa;
    char name[100];
};

int main(){
    struct student s1 ;
    s1.rollNo = 37; 
    s1.cgpa = 9.2;
    strcpy(s1.name, "John");

    printf("student data: \n name: %s\n roll no: %d\n cgpa: %f\n ", s1.name, s1.rollNo, s1.cgpa);

    return 0;
}
*/