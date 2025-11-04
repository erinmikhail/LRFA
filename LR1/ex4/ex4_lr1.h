#ifndef EX4_LR1_H
#define EX4_LR1_H


#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#include <math.h>


double power(double x, int n);
double factorial(int n);
int is_converged(double current, double previous, double precision);
double harmonic_number(int n);


double newton_method(double (*f)(double), double (*df)(double), double x0, double precision);


double f_e(double x);
double df_e(double x);
double f_pi(double x);
double df_pi(double x);
double f_ln2(double x);
double df_ln2(double x);
double f_sqrt2(double x);
double df_sqrt2(double x);
double f_gamma(double x);
double df_gamma(double x);


double calc_e_limit(double precision);
double calc_e_series(double precision);
double calc_e_equation(double precision);

double calc_pi_limit(double precision);
double calc_pi_series(double precision);
double calc_pi_equation(double precision);

double calc_ln2_limit(double precision);
double calc_ln2_series(double precision);
double calc_ln2_equation(double precision);

double calc_sqrt2_limit(double precision);
double calc_sqrt2_series(double precision);
double calc_sqrt2_equation(double precision);

double calc_gamma_limit(double precision);
double calc_gamma_series(double precision);
double calc_gamma_equation(double precision);


void print_results(const char* name, double limit_val, double series_val, double equation_val, double exact_val, double precision);

#endif