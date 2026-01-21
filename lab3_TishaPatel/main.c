#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "operations.h"
#include "display.h"

#define INITIAL_CAPACITY 10  /* Initial memory allocated to store accounts */
#define RESIZE_FACTOR 2      /* Factor by which memory is expanded when capacity is exceeded */
#define TRUE 1               /* For infinite loop condition */
#define MAX_INPUT_LENGTH 100 /* Maximum length for user input */
#define EXPECTED_INPUT 1     /* Expected return value from scanf for valid input */

/* Clear any remaining characters in the input buffer */
static void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Main function to display menu, handle user choice, allocate memory for accounts */
int main(void)
{
    Account **accounts = NULL; /* Dynamic pointer to store account pointers */
    int account_count = 0;     /* Number of accounts currently in the system */
    int choice, account_choice;
    int account_capacity = INITIAL_CAPACITY; /* Current storage capacity */
    int i;
    Account **temp;

    /* Initialize with initial capacity */
    accounts = malloc(INITIAL_CAPACITY * sizeof(Account *));
    if (accounts == NULL)
    {
        fprintf(stderr, "Initial allocation failed.\n");
        return EXIT_FAILURE;
    }

    /* Main program loop */
    while (TRUE)
    {
        /* Display main menu */
        printf("\nBank Account System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display Account Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        /* Get and validate user's menu choice */
        if (scanf("%d", &choice) != EXPECTED_INPUT)
        {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        /* Process choice */
        switch (choice)
        {
        case 1: /* Create a new account and expand storage if full */
            if (account_count >= account_capacity)
            {
                /* Dynamically resize the memory for accounts */
                int new_capacity = account_capacity * RESIZE_FACTOR;
                temp = realloc(accounts, new_capacity * sizeof(Account *));
                if (!temp)
                {
                    printf("Failed to expand account storage due to insufficient memory.\n");
                    break;
                }
                accounts = temp;
                account_capacity = new_capacity; /* Update capacity */
            }

            /* Create a new account */
            accounts[account_count] = create_account(accounts, account_count);
            if (accounts[account_count])
            {
                account_count++;
            }
            break;

        case 2: /* Deposit money */
            deposit(accounts, account_count); /* Let deposit handle account selection */
            break;

        case 3: /* Withdraw money */
            withdraw(accounts, account_count); /* Let withdraw handle account selection */
            break;

        case 4: /* Display account details */
            if (account_count == 0)
            {
                printf("No accounts available.\n");
                break;
            }

            /* Display available accounts and get user's choice */
            printf("Available accounts:\n");
            for (i = 0; i < account_count; i++)
            {
                printf("%d) %s\n", i + 1, accounts[i]->name);
            }
            
            printf("Enter your account choice: ");
            
            if (scanf("%d", &account_choice) != EXPECTED_INPUT || account_choice < 1 || account_choice > account_count)
            {
                printf("Invalid account choice.\n");
                clear_input_buffer();
                break;
            }
            
            clear_input_buffer();
            
            display_details(accounts[account_choice - 1]); /* Pass the selected account directly */

            break;

        case 5: /* Exit the program */
            /* Free all allocated memory before exiting */
            for (i = 0; i < account_count; i++)
            {
                free_account(accounts[i]);
            }
            
            free(accounts);
            
            printf("Exiting the System. Goodbye!\n");
            
            return EXIT_SUCCESS;

        default:
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }
}
