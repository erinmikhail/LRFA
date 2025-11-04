#include "ex6_lr1.h"
#include <math.h>

double trapezoidal_method(double (*f)(double), double a, double b, double epsilon) {
    int n = 1;
    double h = b - a;
    double prev, result;
    
    result = (f(a) + f(b)) * h / 2;
    
    while (1) {
        n *= 2;                    
        h = (b - a) / n;       
        prev = result;           
        
        result = f(a) + f(b);     
        
        for (int i = 1; i < n; i++) {
            double x = a + i * h;  
            result += 2 * f(x);    
        }
        
        result = result * h / 2;   
        
        if (fabs(result - prev) <= epsilon) {
            break;  
        }
        
        // Защита от бесконечного цикла
        if (n > 1000000) {
            printf("Предупреждение: достигнуто максимальное количество итераций\n");
            break;
        }
    }
    
    return result;
}

double function_a(double x) {
    if (x < 1e-10) {
        return 1.0; 
    }
    return log(1.0 + x) / x;
}

double function_b(double x) {
    return exp(-x * x / 2.0);
}

double function_c(double x) {
    if (x > 0.999999) {
        x = 0.999999;
    }
    return log(1.0 / (1.0 - x));
}

double function_d(double x) {
    if (x < 1e-10) {
        return 1.0; 
    }
    return pow(x, x);
}