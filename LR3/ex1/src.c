#include "include.h"

void decimalBase(int number, int r){
    char result[34];

    if (r < 1 || r > 5){
        printf("Error: r must be 1-5\n");
        return;
    }

    int base = 1 << r;

    if (number == 0){
        printf("0\n");
        return;
    }

    int is_mine = 0;
    unsigned int n;

    if (number < 0){
        n = (unsigned int)(-number);
    } else {
        n = (unsigned int)number;
    }

    char digits[34];
    int count = 0;

    while (n > 0){
        int digit = n & (base - 1);

        if (digit < 10){
            digits[count] = '0' + digit;
        } else {
            digits[count] = 'A' + (digit - 10);
        }

        count++;
        n = n >> r;
    }

    int pos = 0;

    if (is_mine) {
        result[0] = '-';
        pos = 1;
    }

    for (int i = count - 1; i >= 0; i--){
        result[pos] = digits[i];
        pos++;
    }

    result[pos] = '\0';
    printf("%s\n", result);
}