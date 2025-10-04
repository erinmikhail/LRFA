#include <stdio.h>
#include <math.h>


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

// циклич возведение в степень
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

// для проверки точности
int is_converged(double current, double previous, double precision){
    return fabs(current - previous) < precision;
}

// Метод Ньют
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

    sum += term;

    while (term > precision && n < 1000){  
        n++;
        term /= n;
        sum += term;
    }
    return sum;
}

double f_e(double x) { return log(x) - 1; }
double df_e(double x) { return 1.0/x; }

double calc_e_equation(double precision) {
    return newton_method(f_e, df_e, 2.0, precision);
}

double calc_pi_limit(double precision){
    double sum = 0.0;
    double previous = -1.0;
    int n = 1;
    int max_iter = 100000;

    sum += 1.0 / (n * n);

    while (!is_converged(sum, previous, precision) && n < max_iter){
        previous = sum;
        n++;
        sum += 1.0 / (n * n);
    }
    return sqrt(6.0 * sum);
}

double calc_pi_series(double precision){
    double sum  = 0.0;
    double previous = -1.0;
    int n = 1;
    int max_iter = 100000;

    sum += 1.0;

    while (!is_converged(4 * sum, 4 * previous, precision) && n < max_iter){
        previous = sum;
        n++;
        double term;
        if (n % 2 == 1) {
            term = 1.0 / (2 * n - 1);
        } else {
            term = -1.0 / (2 * n - 1);
        }
        sum += term;
    }
    return 4 * sum;
}

double f_pi(double x) { return cos(x) + 1; }  
double df_pi(double x) { return -sin(x); }

double calc_pi_equation(double precision) {
    double e = calc_e_series(precision);
    return newton_method(f_pi, df_pi, e, precision);
}

double calc_ln2_limit(double precision) {
    double n = 1.0;
    double current = 0.0;
    double previous = -1.0;
    int max_iter = 100000;
    int iter = 0;
    
    current = n * (pow(2.0, 1.0/n) - 1);
    
    while (!is_converged(current, previous, precision) && iter < max_iter) {
        previous = current;
        n += 1.0;
        current = n * (pow(2.0, 1.0/n) - 1);
        iter++;
    }
    return current;
}

double calc_ln2_series(double precision) {
    double sum = 0.0;
    double previous = -1.0;
    int n = 1;
    int max_iter = 1000000;
    
    sum += 1.0;
    
    while (!is_converged(sum, previous, precision) && n < max_iter) {
        previous = sum;
        n++;
        double term;
        if (n % 2 == 1) {
            term = 1.0 / n;
        } else {
            term = -1.0 / n;
        }
        sum += term;
    }
    return sum;
}

double f_ln2(double x) { 
    double ex = calc_e_series(1e-12);
    return pow(ex, x) - 2; 
}

double df_ln2(double x) { 
    double ex = calc_e_series(1e-12);
    return pow(ex, x) * log(ex); 
}

double calc_ln2_equation(double precision) {
    return newton_method(f_ln2, df_ln2, 0.5, precision);
}

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
    double product = 1.0;
    double previous = -1.0;
    int k = 1;
    int max_iter = 100;

    double exponent = power(2, -k);
    double term = pow(2.0, exponent);
    product *= term;
    
    while (!is_converged(product, previous, precision) && k < max_iter) {
        previous = product;
        k++;
        exponent = power(2, -k);
        term = pow(2.0, exponent);
        product *= term;
    }
    return product;
}

double f_sqrt2(double x) { return x * x - 2; }
double df_sqrt2(double x) { return 2 * x; }

double calc_sqrt2_equation(double precision) {
    return newton_method(f_sqrt2, df_sqrt2, 1.0, precision);
}

double harmonic_number(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

double calc_gamma_limit(double precision) {
    double current = 0.0;
    double previous = -1.0;
    int m = 1;
    int max_iter = 1000000;
    
    current = harmonic_number(m) - log(m);
    
    while (!is_converged(current, previous, precision) && m < max_iter) {
        previous = current;
        m++;
        current = harmonic_number(m) - log(m);
    }
    return current;
}

double calc_gamma_series(double precision) {
    double sum = 0.0;
    double previous = -1.0;
    int k = 2;
    int max_iter = 100000;
    
    double pi = calc_pi_series(precision);
    sum = -pi * pi / 6.0;
    
    while (!is_converged(sum, previous, precision) && k < max_iter) {
        previous = sum;
        double term = (1.0 / (k * sqrt(k))) - (1.0 / k);
        sum += term;
        k++;
    }
    return sum;
}

double f_gamma(double x) {
    return exp(-x) - (1.0 / (x + 1));
}

double df_gamma(double x) {
    return -exp(-x) + (1.0 / ((x + 1) * (x + 1)));
}

double calc_gamma_equation(double precision) {
    double e = calc_e_series(precision);
    return newton_method(f_gamma, df_gamma, 0.5, precision);
}

void print_results(const char* name, double limit_val, double series_val, double equation_val, double exact_val, double precision) {
    printf("%s:\n", name);
    printf("  Предел:    %.*f (ошибка: %.2e)\n", (int)(-log10(precision)) + 1, limit_val, fabs(limit_val - exact_val));
    printf("  Ряд:       %.*f (ошибка: %.2e)\n", (int)(-log10(precision)) + 1, series_val, fabs(series_val - exact_val));
    printf("  Уравнение: %.*f (ошибка: %.2e)\n", (int)(-log10(precision)) + 1, equation_val, fabs(equation_val - exact_val));
    printf("\n");
}

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