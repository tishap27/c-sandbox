#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "account.h"
#include "operations.h"

/* Clear any remaining characters in the input buffer 
 * This function ensures that invalid input does not interfere
 * with subsequent user prompts.
 */
static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Add a transaction to the account's transaction history
 * This function dynamically expands the transaction array and stores the details of the new transaction.
 * Parameters:
 *   account - Pointer to the Account structure where the transaction will be added
 *   type - Type of transaction (e.g., "Deposit", "Withdrawal")
 *   amount - Amount involved in the transaction
 * If memory allocation fails, the function prints an error message.
 */
static void add_transaction(Account* account, const char* type, float amount) {
    Transaction* new_trans;
    time_t now;
    struct tm* timeinfo;
    char timestamp[MAX_TIMESTAMP_LENGTH];

    /* Dynamically allocate memory for the new transaction */
    new_trans = (Transaction*)realloc(account->transactions,
                                      (account->transaction_count + 1) * sizeof(Transaction));
    if (new_trans == NULL) {
        printf("Transaction failed!\n");
        return;
    }

    /* Update the account's transaction array with the new memory */
    account->transactions = new_trans;

    /* Store transaction details */
    strcpy(account->transactions[account->transaction_count].type, type);
    account->transactions[account->transaction_count].amount = amount;

    /* Generate timestamp for the transaction */
    now = time(NULL);
    timeinfo = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    strcpy(account->transactions[account->transaction_count].timestamp, timestamp);

    /* Increment the transaction count */
    account->transaction_count++;
}
/* Function to select a sub-account for deposit or withdrawal */

Account* select_sub_account(Account** accounts, int account_count) {
    int i, account_choice;
    int sub_account_count = 0;
    int* sub_account_indices; /* Dynamically allocate memory for sub-account indices */
    Account* selected_account = NULL;
    int sub_account_choice; /* Declare at the top */

    if (account_count == 0) {
        printf("No accounts available.\n");
        return NULL;
    }

    /* Allocate memory for sub-account indices */
    sub_account_indices = (int*)malloc(account_count * sizeof(int));
    if (sub_account_indices == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    /* Display available account holders */
    printf("Available account holders:\n");
    for (i = 0; i < account_count; i++) {
        printf("%d) %s\n", i + 1, accounts[i]->name);
    }

    /* Get user's choice for account holder */
    printf("Enter your account holder choice: ");
    if (scanf("%d", &account_choice) != EXPECTED_INPUT || account_choice < 1 || account_choice > account_count) {
        printf("Invalid account holder choice.\n");
        clear_input_buffer();
        free(sub_account_indices); /* Free allocated memory */
        return NULL;
    }
    clear_input_buffer();
    account_choice--; /* Adjust for 0-based index */

    /* Display sub-accounts for the selected account holder */
    printf("Available accounts of %s are:\n", accounts[account_choice]->name);
    for (i = 0; i < account_count; i++) {
        if (strcmp(accounts[account_choice]->name, accounts[i]->name) == 0) {
            sub_account_indices[sub_account_count] = i; /* Store index of sub-account */
            sub_account_count++;
            printf("   %d) %s\n", sub_account_count, accounts[i]->type);
        }
    }

    /* Get user's choice for sub-account */
    printf("Enter your account choice: ");
    if (scanf("%d", &sub_account_choice) != EXPECTED_INPUT || sub_account_choice < 1 || sub_account_choice > sub_account_count) {
        printf("Invalid account choice.\n");
        clear_input_buffer();
        free(sub_account_indices); /* Free allocated memory */
        return NULL;
    }
    clear_input_buffer();

    /* Return the selected sub-account */
    selected_account = accounts[sub_account_indices[sub_account_choice - 1]];

    free(sub_account_indices); /* Free allocated memory */
    return selected_account;
}
/* Deposit money into an account
 * This function adds a specified amount to the account balance and records the deposit as a transaction.
 * Parameters:
 *  account - Pointer to the Account structure where money will be deposited
 * Also If the account pointer is NULL or if an invalid amount is entered,an error message is printed.
 */
void deposit(Account** accounts, int account_count) {
    float amount;

    Account* selected_account = select_sub_account(accounts, account_count);
    
    if (selected_account == NULL) {
        return; /* No valid selection was made */
    }

    
    
    /* Prompt user for deposit amount */
    printf("Enter deposit amount: ");
    if (scanf("%f", &amount) != EXPECTED_INPUT || amount < MIN_TRANSACTION_AMOUNT) {
        printf("Invalid amount! Deposit amount must be at least %.2f.\n", MIN_TRANSACTION_AMOUNT);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    /* Update account balance and record transaction */
    selected_account->balance += amount;
    add_transaction(selected_account, "Deposit", amount);

    /* Confirm successful deposit to user */
    printf("Deposited $%.2f to account ID %04d. New balance: $%.2f\n",
        amount, selected_account->id, selected_account->balance);
    }


/* Withdraw money from an account
 * This function deducts a specified amount from the account balance and records the withdrawal as a transaction.
 * Parameters:
 * account - Pointer to the Account structure where money will be withdrawn
 * If insufficient funds are available or an invalid amount is entered, an error message will be displayed.
 */
void withdraw(Account** accounts, int account_count) {
    float amount;
    Account* selected_account = select_sub_account(accounts, account_count);

    if (selected_account == NULL) {
        return; /* No valid selection was made */
    }

   

    /* Check if withdrawals are allowed for this type of account */
    if (strcmp(selected_account->type, "Readiline") == 0) {
        printf("Error: Withdrawals not allowed for Readiline accounts!\n");
        return;
    }

    /* Prompt user for withdrawal amount */
    printf("Enter withdrawal amount: ");
    if (scanf("%f", &amount) != EXPECTED_INPUT || amount < MIN_TRANSACTION_AMOUNT) {
        printf("Invalid amount! Withdrawal must be at least %.2f.\n", MIN_TRANSACTION_AMOUNT);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    /* Check if sufficient funds are available */
    if (amount > selected_account->balance) {
        printf("Insufficient funds!\n");
        return;
    }

    /* Update account balance and record transaction */
    selected_account->balance -= amount;
    add_transaction(selected_account, "Withdrawal", amount);

    /* Confirm successful withdrawal to user */
    printf("Withdrawn $%.2f from account ID %04d. New balance: $%.2f\n",
        amount, selected_account->id, selected_account->balance);
}
