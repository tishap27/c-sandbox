#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* findSubStr(char * str, char *subStr){
    int sublen = strlen(subStr); 
    int len = strlen(str); 
    int i, j;

    for(i = 0 ; i <= (strlen - sublen); i++){
        for(j=0; j < sublen ; j++){
            if(str[i+j] != subStr[j])
            break; 
        }
        if(j == sublen)
        return str + i ;  
    }
    return NULL; 
}

int main(){
    char str[100]; char subStr[50]; 
    
    printf("Enter the main string: ");
    fgets(str, sizeof(str), stdin);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }

    printf("Enter the sub string: ");
    fgets(subStr, sizeof(subStr), stdin);

    for (int i = 0; subStr[i] != '\0'; i++) {
        if (subStr[i] == '\n') {
            subStr[i] = '\0';
            break;
        }
    }

    size_t len = strlen(subStr);
    if (len > 0 && subStr[len - 1] == '\n') {   //better approcah than for loop
        subStr[len - 1] = '\0';
    }


    char *result = findSubStr(str, subStr);

    if (result != NULL) {
        printf("Substring found at position: %ld\n", result - str);
        printf("The substring starts at: \"%s\"\n", result);
    } else {
        printf("Substring not found.\n");
    }

    return 0;
}




















/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int is_palindrome(char *str){
    int len = 0 ; int i ; 
    
    while(str[len])len++;

    for(i = 0 ; i <len/2 ; i ++){
        if(str[i] != str[len - i - 1]){
            return 0;
        }
    }
    return 1; 

}


int main(){
    char str[100];
    int result; 
    printf("Enter string:");
   scanf("%99s", str);

    result = is_palindrome(str); 
    if(result){
        printf("%s is palindrome",str);
    }
    else{
        printf("Not palindrome");
    }
    return 0 ; 
}


*/




















/*#include <stdio.h>

void to_upper(char *str){

    while(*str){
        if(*str>='a' && *str <= 'z')
        *str -= ('a' - 'A'); 
        str ++; 
    }

}

int main(){
    char str[100]; 

    printf("Enter string:");
    scanf("%99s", str); 

    to_upper(str); 
    printf("The converted string is: %s", str); 


    return 0 ; 
}

*/













/*#include <stdio.h>
void removeSpace(char *str){
    char *dst = str; 
    while(*str){
        if(*str != ' ') *dst++ = *str ; 
        str ++ ; 
    }
    *dst = '\0'; 
}

int main(){
    char str[100];
    printf("Enter string:"); 
    fgets(str, sizeof(str), stdin); 

    removeSpace(str); 
    printf("THE STRING AFTER WHITESPACE REMOVAL IS : %s\n", str); 

    return 0;
}

*/














/*#include <stdio.h>


char* findChar(char *str, char ch){
    while(*str && (*str != ch )){
        str++;
    }       
    return (*str == ch) ? str : NULL; 
} 

int main(){
char str[100],ch ; 
char* result; 
printf("Enter string:"); 
fgets(str, sizeof(str), stdin); 

printf("enter char to find:") ;
scanf(" %c", &ch);

result = findChar(str, ch);

if (result ){
    printf("The position at char found is %ld\n", result -str +1); 
}
else 
    printf("Not found \n");

    return 0;
}

*/


















/*#include <stdio.h>

void str_cpy( char *dest, const char * src){

    while ((*dest++ = *src++)); 
}

int main(){
    char src[100]; 
    char dest [100]; 

    printf("Enter src string :");
    scanf("%99s", src); 
    

    str_cpy(dest, src); 
    printf("The string is: %s\n", dest); 

    return 0 ;
}

*/








/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int vowel_count(char *str){
    int count = 0 ; 
    
    while(*str){
        if(*str == 'a' || *str == 'e' || *str == 'i'  || *str == 'o' || *str == 'u'){
            count++ ; 
           }
            str++;
    }
    return count; 
}

int main(){
char str[100]; 
printf("Enter string:"); 
scanf("%99s",str);



printf("The vowel count is: %d\n", vowel_count(str)); 
    return 0;
}


//#include <stdio.h>
//int count_vowels(char *str) {
//    int count = 0;
//    while (*str) {
//        if (*str == 'a' || *str == 'e' || *str == 'i' || 
//            *str == 'o' || *str == 'u' || 
//            *str == 'A' || *str == 'E' || *str == 'I' || 
//            *str == 'O' || *str == 'U') count++;
//        str++;
//    }
//    return count;
//}
//
//int main() {
//    char str[100];
//    printf("Enter a string: ");
//    scanf("%99s", str);
//    printf("Vowel count: %d\n", count_vowels(str));
//    return 0;
//}
//
*/








/*#include <stdio.h>

int str_length(char *str){
    int len =0; 

    while(str[len] != '\0'){
        len++ ; 
    }
    return len; 
}


int main(){
 char str[100]; 

 printf("enter string:"); 
 scanf("%99s", str); 

 printf("Length is : %d \n ", str_length(str));
    return 0 ;
}*/