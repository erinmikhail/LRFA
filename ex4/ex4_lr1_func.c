#include <stdio.h>
#include <math.h>
#include "ex4_lr1.h"

// Вспомогательные функции
double power(double x, int n){
    double result = 1.0;
    for (int i = 0; i < n; i++){ 
        result *= x;
    }
    return result;
}

double factorial(int n){
    double result = 1.0;
    for(int i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

int is_converged(double current, double previous, double precision){
    return fabs(current - previous) < precision;
}

double harmonic_number(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

// Метод Ньютона
double newton_method(double (*f)(double), double (*df)(double), double x0, double precision) {
    double x = x0;
    double x_prev = x0 + 2 * precision; 
    int max_iter = 1000;
    int iter = 0;
    
    while (fabs(x - x_prev) > precision && iter < max_iter) {
        x_prev = x;
        double fx = f(x);       
        double dfx = df(x);      
        
        if (fabs(dfx) < precision) {
            break;
        }
        
        x = x - fx / dfx;
        iter++;
    }
    
    return x;
}

// Функции для уравнений
double f_e(double x) { return log(x) - 1; }
double df_e(double x) { return 1.0/x; }

double f_pi(double x) { return sin(x); }  // Изменено: sin(x) = 0 при x = π
double df_pi(double x) { return cos(x); }

double f_ln2(double x) { 
    return exp(x) - 2.0;  // Упрощенная версия: e^x = 2
}

double df_ln2(double x) { 
    return exp(x);
}

double f_sqrt2(double x) { return x * x - 2; }
double df_sqrt2(double x) { return 2 * x; }

double f_gamma(double x) {
    // Упрощенная функция для тестирования
    return exp(-x) - tgamma(1.0 + x);
}

double df_gamma(double x) {
    // Производная упрощенной функции
    return -exp(-x);
}

// Вычисление e
double calc_e_limit(double precision){
    double n = 1.0;
    double current = 0.0;
    double previous = -1.0;
    int max_iter = 1000000;    
    int iter = 0;

    current = pow(1.0 + 1.0/n, n);

    while (!is_converged(current, previous, precision) && iter < max_iter){
        previous = current;
        n *= 2;
        current = pow(1.0 + 1.0/n, n);
        iter++;
    }
    return current;
}

double calc_e_series(double precision){
    double sum = 0.0;
    double term = 1.0;
    int n = 0;

    while (term > precision && n < 1000){  
        sum += term;
        n++;
        term /= n;
    }
    return sum;
}

double calc_e_equation(double precision) {
    return newton_method(f_e, df_e, 2.0, precision);
}

// Вычисление π
double calc_pi_limit(double precision){
    double sum = 0.0;
    double previous = -1.0;
    int n = 1;
    int max_iter = 100000;

    while (n < max_iter){
        sum += 1.0 / (n * n);
        
        if (n > 1 && is_converged(sqrt(6.0 * sum), sqrt(6.0 * previous), precision)) {
            break;
        }
        
        previous = sum;
        n++;
    }
    return sqrt(6.0 * sum);
}

double calc_pi_series(double precision){
    double sum  = 0.0;
    int n = 0;
    int max_iter = 1000000;
    
    while (n < max_iter) {
        double term = (n % 2 == 0) ? 1.0 / (2 * n + 1) : -1.0 / (2 * n + 1);
        sum += term;
        
        if (n > 0 && fabs(4 * term) < precision) {
            break;
        }
        n++;
    }
    return 4 * sum;
}

double calc_pi_equation(double precision) {
    return newton_method(f_pi, df_pi, 3.0, precision);
}

// Вычисление ln(2) - ИСПРАВЛЕННЫЕ ВЕРСИИ
double calc_ln2_limit(double precision) {
    // Более стабильный метод: ln(1+x) ≈ x - x²/2 + x³/3 - ... при x=1
    double x = 1.0;
    double sum = 0.0;
    double term = x;
    int n = 1;
    int max_iter = 1000000;
    
    while (n <= max_iter && fabs(term) > precision) {
        sum += term;
        n++;
        term = (n % 2 == 1) ? 1.0 / n : -1.0 / n;
    }
    return sum;
}

double calc_ln2_series(double precision) {
    // Альтернативный ряд: ln(2) = Σ(1/(n * 2^n)) для n=1 до ∞
    double sum = 0.0;
    double term = 1.0;
    int n = 1;
    int max_iter = 1000;
    
    while (n <= max_iter) {
        term = 1.0 / (n * pow(2, n));
        sum += term;
        
        if (fabs(term) < precision) {
            break;
        }
        n++;
    }
    return sum;
}

double calc_ln2_equation(double precision) {
    return newton_method(f_ln2, df_ln2, 0.5, precision);
}

// Вычисление √2
double calc_sqrt2_limit(double precision) {
    double x = 1.0;
    double x_prev = 0.0;
    int max_iter = 100;
    int iter = 0;
    
    while (fabs(x - x_prev) > precision && iter < max_iter) {
        x_prev = x;
        x = 0.5 * (x + 2.0 / x);
        iter++;
    }
    return x;
}

double calc_sqrt2_series(double precision) {
    // Используем биномиальное разложение
    double sum = 1.0;
    double term = 0.5;
    int n = 1;
    int max_iter = 100;
    
    while (n <= max_iter && fabs(term) > precision) {
        sum += term;
        n++;
        // Коэффициенты биномиального ряда для √(1+1)
        term = term * (3 - 2*n) / (2 * n);
    }
    return sum;
}

double calc_sqrt2_equation(double precision) {
    return newton_method(f_sqrt2, df_sqrt2, 1.0, precision);
}

// Вычисление γ
double calc_gamma_limit(double precision) {
    double current = 0.0;
    double previous = -1.0;
    int m = 1;
    int max_iter = 1000000;
    
    while (m < max_iter) {
        current = harmonic_number(m) - log(m);
        
        if (m > 1 && is_converged(current, previous, precision)) {
            break;
        }
        
        previous = current;
        m++;
    }
    return current;
}

double calc_gamma_series(double precision) {
    // Упрощенный ряд для тестирования
    double sum = 0.0;
    int k = 2;
    int max_iter = 100000;
    
    while (k < max_iter) {
        double term = (1.0/k - log((k+1.0)/k));
        sum += term;
        
        if (fabs(term) < precision) {
            break;
        }
        k++;
    }
    return sum;
}

double calc_gamma_equation(double precision) {
    return newton_method(f_gamma, df_gamma, 0.5, precision);
}

// Функция вывода результатов
void print_results(const char* name, double limit_val, double series_val, double equation_val, double exact_val, double precision) {
    printf("%s:\n", name);
    printf("  Предел:    %.*f (ошибка: %.2e)\n", (int)(-log10(precision)) + 1, limit_val, fabs(limit_val - exact_val));
    printf("  Ряд:       %.*f (ошибка: %.2e)\n", (int)(-log10(precision)) + 1, series_val, fabs(series_val - exact_val));
    printf("  Уравнение: %.*f (ошибка: %.2e)\n", (int)(-log10(precision)) + 1, equation_val, fabs(equation_val - exact_val));
    printf("\n");
}