#include <stdio.h>

int str_cmp(const char *a , const char *b){
    while(*a &&(*a == *b)){
        a++ ; 
        b++ ; 
    }
    printf("%d", *(unsigned char *) a - *(unsigned char *)b);
    return *(unsigned char *) a - *(unsigned char *)b ; 
}


int main(){
        char str1[100]; char str2[100]; int result;

        printf("enter str1:");
        scanf("%99s", str1); 

        printf("enter str2:");
        scanf ("%99s", str2); 

        result = str_cmp(str1, str2); 
        if(result == 0){
            printf("%d\n", result);
            printf("Strings are equal\n"); 
        }
        else if(result > 0) {
            printf("String 1 is greater\n"); 
        }
        else if (result<0){
            printf("string2 is greater\n"); 
        } 
        
        
    return 0 ;
}























/*#include <stdio.h>

void str_concat(char *dest, char*src){

    while(*dest) dest++; 
    while((*dest++ = *src++));
}

int main(){
    char str1[200] = "Hello";
    char str2[100] = "World";

    str_concat(str1, str2); 
    printf("whole string is : %s\n", str1); 

    return 0 ; 
}*/