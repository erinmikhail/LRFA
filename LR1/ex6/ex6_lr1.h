#ifndef EX6_LR1_H
#define EX6_LR1_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double trapezoidal_method(double (*f)(double), double a, double b, double epsilon);


double function_a(double x);
double function_b(double x);
double function_c(double x);
double function_d(double x);

#endif