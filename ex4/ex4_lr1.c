#include <stdio.h>
#include <math.h>
#include "ex4_lr1.h"

int main() {
    double precision;

    printf("Введите точность: ");
    scanf("%lf", &precision);

    printf("Вычисление e: \n");
    double e_limit = calc_e_limit(precision);
    double e_series = calc_e_series(precision);
    double e_equation = calc_e_equation(precision);
    print_results("e (число Эйлера)", e_limit, e_series, e_equation, M_E, precision);

    printf("Вычисление π...\n");
    double pi_limit = calc_pi_limit(precision);
    double pi_series = calc_pi_series(precision);
    double pi_equation = calc_pi_equation(precision);
    print_results("π (число Пи)", pi_limit, pi_series, pi_equation, M_PI, precision);
    
    printf("Вычисление ln(2)...\n");
    double ln2_limit = calc_ln2_limit(precision);
    double ln2_series = calc_ln2_series(precision);
    double ln2_equation = calc_ln2_equation(precision);
    print_results("ln(2)", ln2_limit, ln2_series, ln2_equation, log(2), precision);
    
    printf("Вычисление √2...\n");
    double sqrt2_limit = calc_sqrt2_limit(precision);
    double sqrt2_series = calc_sqrt2_series(precision);
    double sqrt2_equation = calc_sqrt2_equation(precision);
    print_results("√2", sqrt2_limit, sqrt2_series, sqrt2_equation, sqrt(2), precision);
    
    printf("Вычисление γ...\n");
    double gamma_limit = calc_gamma_limit(precision);
    double gamma_series = calc_gamma_series(precision);
    double gamma_equation = calc_gamma_equation(precision);
    
    printf("γ (постоянная Эйлера):\n");
    printf("  Предел:    %.*f\n", (int)(-log10(precision)) + 1, gamma_limit);
    printf("  Ряд:       %.*f\n", (int)(-log10(precision)) + 1, gamma_series);
    printf("  Уравнение: %.*f\n", (int)(-log10(precision)) + 1, gamma_equation);
    printf("  Ожидается: 0.5772156649\n");
    printf("  Ошибка предела:    %.2e\n", fabs(gamma_limit - 0.5772156649));
    printf("  Ошибка ряда:       %.2e\n", fabs(gamma_series - 0.5772156649));
    printf("  Ошибка уравнения:  %.2e\n", fabs(gamma_equation - 0.5772156649));
    
    return 0;
}