#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "account.h"

/* Clear leftover input from the buffer */
static void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int generate_unique_id(Account** accounts, int account_count) {
    static int current_id = 999; /* Start just below 1000 so current_id++ doesnt skip 1000*/
    int i, is_unique;
    int attempts = 0; /* Counter to track how many IDs have been checked */

    /* Validate input */
    if (accounts == NULL || account_count < 0) {
        fprintf(stderr, "Error: Invalid accounts array or account count\n");
        exit(EXIT_FAILURE);
    }

    do {
        current_id++; /* Increment the ID */
        /* Reset to 1000 if exceeding 4-digit range */
        if (current_id > 9999) {
            current_id = 1000;
        }
        is_unique = TRUE; /* Assume the ID is unique */

        /* Check if the incremented ID already exists */
        for (i = 0; i < account_count; i++) {
            if (accounts[i] != NULL && accounts[i]->id == current_id) {
                is_unique = FALSE; /* ID is not unique */
                break;
            }
        }
        attempts++; /* Increment attempts counter */
        /* Check if all possible IDs have been exhausted */
        if (attempts > TOTAL_POSSIBLE_IDS) { /* Total possible IDs: 9000 (9999 - 1000 + 1) */
            fprintf(stderr, "Error: No more 4 DIGIT unique IDs are available (all IDs used)\n");
            exit(EXIT_FAILURE); /* Exit program */
        }
    } while (!is_unique); /* Repeat until a unique ID is found */

    return current_id;
}

/*Function to handle invalid names such as just number '1234' or blank spaces*/
static int is_valid_name(const char* name) {
    int i;
    int has_alpha = 0; /* Flag to check for alphabetic characters */

    /* Check if the name is NULL or empty */
    if (name == NULL || name[0] == '\0') {
        return 0; /* Invalid name */
    }

    /* Check if the name contains only whitespace or non-alphabetic characters */
    for (i = 0; name[i] != '\0'; i++) {
        if (!isspace((unsigned char)name[i])) {
            if (isalpha((unsigned char)name[i])) {
                has_alpha = 1; /* Name contains at least one alphabetic character */
            }
        }
    }

    return has_alpha; /* Valid only if it contains at least one alphabetic character */
}


/* Create and initialize a new bank account */
Account* create_account(Account** accounts, int account_count)
{
    Account* new_account;
    float initial_balance;
    int type_choice;
    time_t now;
    struct tm* timeinfo;
    char timestamp[MAX_TIMESTAMP_LENGTH];
    int i;

    /* Allocate memory for new account structure */
    new_account = (Account*)malloc(sizeof(Account));
    if (new_account == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new account\n");
        return NULL;
    }

    /* Get and validate account holder's name */
    do {
        printf("Enter account holder's name: ");
        fgets(new_account->name, MAX_NAME_LENGTH, stdin);
        new_account->name[strcspn(new_account->name, "\n")] = '\0'; /* Remove newline */

        if (!is_valid_name(new_account->name)) {
            printf("Error: Invalid name. Please enter a valid name.\n");
        }
    } while (!is_valid_name(new_account->name)); /* Repeat until a valid name is entered */

    /* Check if an account with the same name already exists */
    for (i = 0; i < account_count; i++) {
        if (strcmp(accounts[i]->name, new_account->name) == 0) {
            printf("Account holder '%s' already exists. Creating a sub-account.\n", new_account->name);
            break; /* Exit loop if name matches */
        }
    }

    /* Get and validate initial deposit amount */
    printf("Enter initial deposit amount: ");
    if (scanf("%f", &initial_balance) != 1 || initial_balance < 0) {
        fprintf(stderr, "Error: Invalid initial balance amount. Enter a positive amount.\n");
        free(new_account);
        return NULL;
    }
    clear_input_buffer();

    /* Get and validate account type selection */
    printf("Select account type:\n1. Chequing\n2. Savings\n3. Readiline\nEnter your choice: ");
    if (scanf("%d", &type_choice) != EXPECTED_INPUT || type_choice < CHEQUING || type_choice > READILINE) {
        printf("Warning: Invalid account type selected. Using Chequing as default\n");
        type_choice = CHEQUING;
    }
    clear_input_buffer();

    /* Initialize account properties */
    new_account->id = generate_unique_id(accounts, account_count);  /* Generate 4-digit ID */
    new_account->balance = initial_balance;
    new_account->transaction_count = 1;  /* Count initial deposit as first transaction */

    /* Set account type based on user selection */
    switch (type_choice) {
        case 1: strncpy(new_account->type, "Chequing", MAX_TYPE_LENGTH); break;
        case 2: strncpy(new_account->type, "Savings", MAX_TYPE_LENGTH); break;
        case 3: strncpy(new_account->type, "Readiline", MAX_TYPE_LENGTH); break;
    }

    /* Allocate memory for transaction history */
    new_account->transactions = (Transaction*)malloc(sizeof(Transaction));
    if (new_account->transactions == NULL) {
        fprintf(stderr, "Error: Failed to allocate transaction memory\n");
        free(new_account);
        return NULL;
    }

    /* Record initial deposit transaction */
    strncpy(new_account->transactions[0].type, "Deposit", 10);
    new_account->transactions[0].amount = initial_balance;

    /* Generate timestamp for initial transaction */
    now = time(NULL);
    timeinfo = localtime(&now);
    strftime(timestamp, MAX_TIMESTAMP_LENGTH, "%Y-%m-%d %H:%M:%S", timeinfo);
    strncpy(new_account->transactions[0].timestamp, timestamp, MAX_TIMESTAMP_LENGTH);

    /* Confirm account creation to user */
    printf("\nAccount created successfully for %s with an initial balance of $%.2f.\n", new_account->name, new_account->balance);
    printf("Account ID: %04d\n", new_account->id);
    printf("Account Type: %s\n", new_account->type);

    return new_account;
}


/* Properly deallocate account memory */
void free_account(Account* account)
{
    if (account != NULL) {
        /* Free transaction history first */
        if (account->transactions != NULL) {
            free(account->transactions);
        }
        /* Free account structure itself */
        free(account);
    }
}
