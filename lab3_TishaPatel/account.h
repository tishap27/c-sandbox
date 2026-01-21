/* ACCOUNT MANAGEMENT SYSTEM HEADER */
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <time.h>  /* For time-related functions */

/* Maximum lengths for various data fields */
#define MAX_NAME_LENGTH 50       /* Longest allowed name length */
#define MAX_TYPE_LENGTH 20       /* Max length for account/transaction type */
#define MAX_TIMESTAMP_LENGTH 20  /* Date-time string storage size */
#define TOTAL_POSSIBLE_IDS 9000 /* There are Total 9000 possible 4 digit IDs (9999 - 1000 + 1)*/
#define MAX_ACCOUNTS 20 
#define TRUE 1
#define FALSE 0
#define CHEQUING 1
#define SAVINGS 2
#define READILINE 3
#define EXPECTED_INPUT 1

/* transaction record structure */
typedef struct Transaction {
    char type[MAX_TYPE_LENGTH];      /*  type: Deposit/Withdrawal */
    float amount;                    
    char timestamp[MAX_TIMESTAMP_LENGTH]; /* Date-time in YYYY-MM-DD HH:MM:SS format */
} Transaction;

/* Bank account structure definition */
typedef struct Account {
    int id;                         /* Unique 4-digit account identifier */
    char name[MAX_NAME_LENGTH];     /* Account holder's full name */
    float balance;                  /* Current account balance in dollars */
    char type[MAX_TYPE_LENGTH];     /* Account type: Chequing/Savings/Readiline */
    Transaction* transactions;      /* Array of financial transactions */
    int transaction_count;          /* Number of stored transactions */
} Account;

/* FUNCTION PROTOTYPES */
/* Creates new account with user input */
Account* create_account(Account** accounts, int account_count);

/* Releases all memory associated with an account */
void free_account(Account* account);

#endif /* ACCOUNT_H */
