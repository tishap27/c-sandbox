#include <stdio.h>
#include <stdlib.h>

void sortArray(int array[] , int size){
    int i,j, temp; 

    for(i=0; i < size -1; i++){
        for(j=0; j < size -i -1; j++){
            if(array[j]> array[j+1]){
                temp = array[j];
                array[j]= array[j+1];
                array[j+1]= temp;
            }
        }
    }
}

void printInfo(int array[], int size){
    int i;

    for(i = 0; i< size; i++){
        printf("%d\t", array[i]);
    }
}


int main(){
    int arr[]= {9,3,6,8,5,2,7,4};
    int size; 
    size = sizeof(arr)/ sizeof(arr[0]);

    sortArray(arr, size);
    printInfo(arr, size);
    printf("\n");



    return 0;
}