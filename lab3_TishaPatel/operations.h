/* ACCOUNT OPERATIONS HEADER */
#ifndef OPERATIONS_H
#define OPERATIONS_H

#define MIN_TRANSACTION_AMOUNT 1.00    /*minimum amount required for withdrawal and deposit*/
#include "account.h"

/* Function to deposit money into an account This function allows adding funds to the specified account.
 * It will update the account balance and record the transaction.
 * Parameters:
 * account - Pointer to the Account structure to be credited
 * The function will prompt the user for the deposit amount.If the account pointer is NULL, an error message will be shown.
 */
void deposit(Account** account, int account_count);

/* Function to withdraw money from an account This function allows removing funds from the specified account.
 * It will update the account balance and record the transaction.
 * Parameters:
 * account - Pointer to the Account structure to be debited
 * The function will prompt the user for the withdrawal amount.Also handles that Withdrawals are not allowed for Readiline accounts.
 * If the account pointer is NULL or if there are insufficient funds,an error message is printed.
 */
void withdraw(Account** account, int account_count);

#endif /* OPERATIONS_H */
