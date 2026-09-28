#include <stdio.h>

// A clean, error-free program to test standard tokenization
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    int terms = 10;
    
    printf("Fibonacci Series:\n");
    for (int i = 0; i < terms; i++) {
        printf("%d ", fibonacci(i));
    }
    
    return 0;
}