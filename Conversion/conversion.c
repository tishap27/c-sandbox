#include <stdio.h>
#include <stdlib.h>


int main() {
    unsigned int decimal;
    int i;

    printf("Enter a positive decimal number: ");
    scanf("%u", &decimal);

    printf("Decimal: %u\n", decimal);
    printf("Binary: ");
    
    /* Print binary */
    for (i = 31; i >= 0; i--) {
        printf("%d", (decimal >> i) & 1);
    }
    printf("\n");

    printf("Hexadecimal: 0x%X\n", decimal);

    return EXIT_SUCCESS;
}