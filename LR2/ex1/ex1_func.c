#include "ex1.h"
#include <stdarg.h>
#include <math.h>

bool has_finite_rep(double fraction, int base){
    if(fraction <= 0.0 || fraction >= 1.0){
        printf("Ошибка: дробь %.6f должна быть в диапазоне (0;1)\n", fraction);
        return false;
    }

    if (base < 2) {
        printf("Ошибка: основание системы счисления %d должно быть >= 2\n", base);
        return false;
    }

    double product = fraction;
    const int max_iterations = 50;
    
    for (int i = 0; i < max_iterations; i++){
        product *= base;

        double remainder = fabs(product - round(product));
        if (remainder < 1e-8) {
            return true;
        }

        product = product - floor(product);

        if (product < 1e-12) {
            return true;
        }
    }

    return false;
}

const char* get_system_name(enum NumberSystem system) {
    switch (system) {
        case BINARY: return "двоичная";
        case OCTAL: return "восьмеричная";
        case DECIMAL: return "десятичная";
        case HEXADECIMAL: return "шестнадцатеричная";
        case CUSTOM_BASE: return "произвольная";
        default: return "неизвестная";
    }
}

void check_finite_rep_count(enum NumberSystem system, int count, ...){
    va_list args;
    va_start(args, count);
    int base;
    if(system == CUSTOM_BASE){
        base = count;
        count = va_arg(args, int);
    } else {
        base = system;
    }

    printf("=== %s система счисления (основание %d) ===\n", get_system_name(system), base);
    
    for (int i = 0; i < count; i++){
        double fraction = va_arg(args, double);
        bool result = has_finite_rep(fraction, base);

        if (result) {
            printf("  %.10f - имеет конечное представление\n", fraction);
        } else {
            printf("  %.10f - имеет бесконечное представление\n", fraction);
        }
    }

    va_end(args);
    printf("\n");
}

void check_finite_rep_sentinel(enum NumberSystem system, ...) {
    va_list args;
    va_start(args, system);
    
    int base = system;
    if (system == CUSTOM_BASE) {
        base = va_arg(args, int);
    }
    
    printf("=== %s система счисления (основание %d, маркер конца) ===\n", get_system_name(system), base);
    
    double fraction;
    int counter = 0;
    
    while ((fraction = va_arg(args, double)) > 0.0) {
        bool result = has_finite_rep(fraction, base);
        if (result) {
            printf("  %.10f - имеет конечное представление\n", fraction);
            counter++;
        } else {
            printf("  %.10f - имеет бесконечное представление\n", fraction);
            counter++;
        }
    }
    
    va_end(args);
    printf("\n");
}