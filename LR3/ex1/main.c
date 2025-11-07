#include "include.h"

int main () {
    printf("Перевод чисел в системы 2^r\n");
    printf("13 in 2 = ");
    decimalBase(13,1);

    printf("42 in 8 = ");
    decimalBase(42,3);

    printf("31 in 4 = ");
    decimalBase(31,2);

    printf("255 in 16 = ");
    decimalBase(255,4);

    printf("154 in 32 = ");
    decimalBase(154,5);
    return 0;
}