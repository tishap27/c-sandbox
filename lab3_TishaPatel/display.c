#include <stdio.h>
#include <time.h>
#include "account.h"
#include "display.h"


/* Display account details and recent transaction history */
void display_details(Account* account) {
    int i; /* Loop counter for iterating through transactions */
    time_t now; /* Current time for comparison with transaction timestamps */
    time_t transaction_time; /* Parsed transaction timestamp as time_t */
    struct tm timeinfo = {0}; /* Structure to hold parsed date and time components */
    int year, month, day, hour, min, sec; /* Variables to store individual date/time components */
    double seconds; /* Difference in seconds between current time and transaction time */

    if (account == NULL) {
        printf("No account found!\n");
        return;
    }

    /* Display basic account information */
    printf("\nAccount Details:\n");
    printf("Account ID: %04d\n", account->id);
    printf("Holder Name: %s\n", account->name);
    printf("Account Type: %s\n", account->type);
    printf("Current Balance: $%.2f\n", account->balance);

    /* Display transaction history */
    printf("\nTransaction History:\n");
    time(&now);  /* Get current time */
    
    if (account->transaction_count == 0) {
        printf("No transactions available.\n");
        return;
    }

     /* Loop through all transactions */
     for (i = 0; i < account->transaction_count; i++) {
        /* Parse timestamp string into separate date/time components */
        if (sscanf(account->transactions[i].timestamp, 
                 "%d-%d-%d %d:%d:%d",
                 &year, &month, &day, &hour, &min, &sec) != 6) {
            continue;  /* Skip if timestamp format is invalid */
        }

        /* Convert parsed date/time to tm structure */
        timeinfo.tm_year = year - 1900;       /* Adjust year to start from 1900 for tm structure */
        timeinfo.tm_mon = month - 1;          /* Convert month to 0-based index for tm structure*/
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = min;
        timeinfo.tm_sec = sec;

        /* Convert tm structure to time_t for comparison */
        transaction_time = mktime(&timeinfo);
        seconds = difftime(now, transaction_time);

        /* Display transactions from the last 30 days */
        if (seconds <= 30 * 24 * 60 * 60) {
            printf("%s: $%.2f at %s\n", 
                   account->transactions[i].type,
                   account->transactions[i].amount,
                   account->transactions[i].timestamp);
        }
     }
}
