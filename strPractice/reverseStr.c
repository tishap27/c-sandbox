#include <stdio.h>


void reverse_string(char *str){
    int len=0; 
    int i;
    char temp;

    while(str[len] != '\0'){
        len++;
    }
    for(i=0; i<len/2; i++){
        temp = str[i];
        str[i]= str[len - i - 1];
        str[len - i - 1] = temp; 
    }

}
int main(){
    char str[100];

    printf("Enter string:"); 
    scanf("%99s", str);

    reverse_string(str);
    printf("Reversed : %s\n", str); 
    
    return 0;
}