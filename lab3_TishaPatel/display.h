/* ACCOUNT DISPLAY FUNCTIONALITY */
#ifndef DISPLAY_H
#define DISPLAY_H
#include <string.h>
#include <stdlib.h>
#include "account.h"

/* Function to show account information and transaction history and prints out the details of a given account(ID 
 *Account holder's name, type, Current balance)
 * Parameters: account - Pointer to the Account structure to be displayed.If the account pointer is NULL, an error message will be shown.
 */
void display_details(Account* account);

#endif /* DISPLAY_H */
