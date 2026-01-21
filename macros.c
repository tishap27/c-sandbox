#include <stdio.h>

/* Usage of extern with variables */

int a, b = 6;

void func1(void);
void func2(void);

int main(void) {
    printf("Inside main(): a=%d and b=%d\n", a, b);
    func1();
    func2();
    return 0;
}

void func1(void) {
    printf("Inside func1(): a=%d and b=%d\n", a, b);
}

void func2(void) {
    int a = 8;
    printf("Inside func2(): a=%d and b=%d\n", a, b);
}

#define TRUE 1
#define MAX 10
#define SUM(x, y) ((x) + (y))

#define PI 3.14
#define PISQUARE (PI*PI)

/* Example usage of macros */
void example_macro_usage(void) {
    int s = SUM(4,5);
    float k = PISQUARE;
    printf("SUM(4,5) = %d, PISQUARE = %f\n", s, k);
}