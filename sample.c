#include <stdio.h>

int main() {
    // 1. Standard valid constructs
    int i = 0;
    float sum = 3.14;
    
    while (i <= 10) {
        sum = sum + i;
        i++;
    }

    if (sum == 10) {
        printf("Hello, Analyzer!");
    }

    // 2. Intentional Error: Illegal characters
    @
    $

    // 3. Intentional Error: Malformed float (multiple decimals)
    float bad_number = 192.168.1.1;

    // 4. Intentional Error: Unclosed string literal
    char *bad_str = "This string has no closing quote;
    
    return 0;
}