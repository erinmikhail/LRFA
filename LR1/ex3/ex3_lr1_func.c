#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ex3_lr1.h"

void solve_quadratic(double a, double b, double c, double epsilon) {
    printf("Уравнение: (%.2f)x² + (%.2f)x + (%.2f) = 0\n", a, b, c);
    
    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                printf("  Бесконечное количество решений\n");
            } else {
                printf("  Нет решений\n");
            }
        } else {
            double x = -c / b;
            printf("  Линейное уравнение, x = %.6f\n", x);
        }
        return;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (fabs(discriminant) < epsilon) {
        double x = -b / (2 * a);
        printf("  Один корень: x = %.6f\n", x);
    } else if (discriminant > 0) {
        double sqrt_d = sqrt(discriminant);
        double x1 = (-b + sqrt_d) / (2 * a);
        double x2 = (-b - sqrt_d) / (2 * a);
        printf("  Два корня: x1 = %.6f, x2 = %.6f\n", x1, x2);
    } else {
        printf("  Действительных корней нет\n");
    }
}

void generate_perm(double coef[3], double epsilon){
    int used[6] = {0};
    int count = 0;
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (i != j && i != k && j != k) {
                    int is_unique = 1;
                    for (int m = 0; m < count; m++) {
                        if (used[m] == (i * 100 + j * 10 + k)) {
                            is_unique = 0;
                            break;
                        }
                    }
                    
                    if (is_unique) {
                        used[count] = i * 100 + j * 10 + k;
                        count++;
                        solve_quadratic(coef[i], coef[j], coef[k], epsilon);
                    }
                }
            }
        }
    }
}

void handle_q_flag(int argc, char *argv[]){
    if (argc != 6){
        printf("Ошибка: для флага -q нужно 4 параметра\n");
        exit(1);
    }

    double epsilon = atof(argv[2]);
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    double c = atof(argv[5]);

    printf("Точность: %f\n", epsilon);
    printf("Коэффициенты: a=%.2f, b=%.2f, c=%.2f\n\n", a, b, c);

    double coef[3] = {a, b, c};
    generate_perm(coef, epsilon); 
}

void handle_m_flag(int argc, char *argv[]){
    if (argc != 4){
        printf("Неверные параметры для флага -m\n");
        exit(1);
    }

    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);

    if (num1 == 0 || num2 == 0){
        printf("Ошибка: числа не должны быть равны 0\n");
        exit(1);
    }

    if (num1 % num2 == 0){
        printf("Результат: %d кратно %d\n", num1, num2);
    } else if (num2 % num1 == 0){
        printf("Результат: %d кратно %d\n", num2, num1);
    } else {
        printf("Числа не кратны друг другу\n");
    }
}

void handle_t_flag(int argc, char *argv[]){
    if (argc != 6){
        printf("Неверное количество параметров для флага -t\n");
        exit(1);
    }

    double epsilon = atof(argv[2]);
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    double c = atof(argv[5]);

    if (a <= 0 || b <= 0 || c <= 0){
        printf("Ошибка: длины сторон треугольника должны быть положительными\n");
        exit(1);
    }
    
    bool is_right = false;

    if (fabs(a*a + b*b - c*c) < epsilon) {
        is_right = true;
    } else if (fabs(a*a + c*c - b*b) < epsilon) is_right = true;
    else if (fabs(c*c + b*b - a*a) < epsilon) is_right = true;

    if (is_right){
        printf("Треугольник прямоугольный\n");
    } else {
        printf("Треугольник не прямоугольный\n");
    }
}