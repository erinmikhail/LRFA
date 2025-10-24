#include "ex1.h"

int main(){
    printf("Проверка конечности представления дробей в системах счисления\n");
    printf("=============================================================\n\n");
    
    check_finite_rep_count(BINARY, 4, 0.5, 0.25, 0.125, 0.1); 
    check_finite_rep_count(OCTAL, 3, 0.5, 0.125, 0.1);
    check_finite_rep_count(DECIMAL, 4, 0.5, 0.2, 0.1, 0.3333333333);
    check_finite_rep_sentinel(HEXADECIMAL, 0.5, 0.125, 0.0625, 0.1, 0.0);

    printf("=== Произвольные системы счисления ===\n");
    
    check_finite_rep_count(CUSTOM_BASE, 3, 3, 0.2, 0.04, 0.1);
    check_finite_rep_count(CUSTOM_BASE, 5, 3, 0.2, 0.04, 0.1);  
    check_finite_rep_count(CUSTOM_BASE, 7, 3, 0.142857, 0.5, 0.25);  
    check_finite_rep_sentinel(CUSTOM_BASE, 12, 0.5, 0.25, 0.1, 0.0);  
    return 0;
}