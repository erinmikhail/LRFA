#include "ex6_lr1.h"
#include <stdio.h>

int main(){
    double epsilon; 

    printf("Введите точность epsilon: ");
    scanf("%lf", &epsilon); 

    if (epsilon <= 0){
        printf("Ошибка: точность должна быть положительной\n");
        return 1;
    }

    printf("Вычисление интегралов с точностью %e:\n", epsilon);
    printf("a. ∫₀¹ ln(1+x)/x dx = %15.10f\n", trapezoidal_method(function_a, 0, 1, epsilon));
    printf("b. ∫₀¹ e^(-x²/2) dx = %15.10f\n", trapezoidal_method(function_b, 0, 1, epsilon));
    printf("c. ∫₀¹ ln(1/(1-x)) dx = %15.10f\n", trapezoidal_method(function_c, 0, 1, epsilon));
    printf("d. ∫₀¹ x^x dx = %15.10f\n", trapezoidal_method(function_d, 0, 1, epsilon));

    return 0;
}