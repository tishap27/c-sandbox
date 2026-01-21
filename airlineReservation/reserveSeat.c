#include <stdio.h>
#include <stdlib.h>

#define MAX_SEATS 10
#define RESERVE_SEAT 1
#define SAVE_EXIT 2
#define TRUE 1

/*Book Seats*/

typedef struct passenger {
    char name[100]; 
    char passport[20];
    char seat_class[10]; 
    int seat_num; 
}pax;

void reserve_seat(pax passenger[], int *count){
    pax p ; 
    int seat, i ;
    int valid = 1 ; 

    printf("Enter Passenger name:"); 
    scanf("%s", p.name); 
    printf("Enter Passenger passport number:");
    scanf("%s", p.passport); 
    printf("Enter seat class(Porter Reserve/Porter Classic):"); 
    scanf("%s", p.seat_class);
    printf("Enter seat number(1 - %d)", MAX_SEATS); 
    scanf("%d", &seat);
   
    for(i = 0 ; i < *count; i++){
        if(passenger[i].seat_num == seat){
            printf("Seat already reserved.\n"); 
            valid = 0; 
            break;
        }
    }
    if(seat < 1 || seat > MAX_SEATS){
        printf("Invalid seat number. please choose valid seat number.\n");
        valid = 0 ; 
    }
    if(valid){
        p.seat_num = seat; 
        passenger[*count]  = p; 
        (*count)++; 
        printf("Reservation successful for seat %d.\n", seat);
    }
    else{
        printf("Seat already reserved.\n"); 
    }
}

void save_reservations(pax passenger[], int count){
    FILE *fptr = fopen("reservation.txt", "wb"); 
    if(fptr == NULL){
        printf("Allocation failed\n"); 
        return; 
    }
    fwrite(passenger , sizeof(pax), count , fptr);
    fclose(fptr); 
}

int main(){
    pax passengers[MAX_SEATS]; 
    int count = 0 ; 
    int choice; 

    while (TRUE)
    {
        printf("Enter choice \n 1. Reserve Seat\n 2. Save & Exit");
        scanf("%d", &choice); 
            if(choice == RESERVE_SEAT){
                reserve_seat(passengers, &count);
            }
            else if(choice == SAVE_EXIT){
                save_reservations(passengers, count); 
            }
            else{
                printf("Invalid choice choose between 1 and 2.\n"); 
            }
    }
    

    return 0 ; 
}