#ifndef FINITE_REPRESENYAYION_H
#define FINITE_REPRESENYAYION_H

#include <stdbool.h>
#include <stdio.h>

enum NumberSystem{
    BINARY = 2,
    OCTAL = 8,
    DECIMAL = 10,
    HEXADECIMAL = 16,
    CUSTOM_BASE = 0
};

bool has_finite_rep(double fractoin, int base);
void check_finite_rep_count(enum NumberSystem system, int count, ...);
void check_finite_rep_sentinel(enum NumberSystem system, ...);
const char* get_system_name(enum NumberSystem system);

#endif