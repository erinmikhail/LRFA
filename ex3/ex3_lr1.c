#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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
                        used[count++] = i * 100 + j * 10 + k;
                        solve_quadratic(coef[i], coef[j], coef[k], epsilon);
                    }
                }
            }
        }
    }
}


void handle_q_flag(int argc, char *argv[]){

    if (argc != 6){ // 4 параметра + флаг + имя проги
        printf("Ошибка, для этого флага нужно 4 парамаетра\n");
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
        printf("Неверные параметры для этого флага\n");
        exit(1);
    }

    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);

    if (num1 == 0 || num2 == 0){
        printf("Числа не должны быть равны 0");
        exit(1);
    }

    if (num1 % num2 == 0){
        printf("Результат: %d крактно %d\n", num1, num2);
    } else if (num2 % num1 == 0){
        printf("Результат: %d крактно %d\n", num2, num1);
    } else {
        printf("Числа не кратны друг другу");
    }
}

void handle_t_flag(int argc, char *argv[]){

    if (argc != 6){
        printf("Невероне кол-во параметров для этого флага\n");
        exit(1);
    }

    double epsilon = atof(argv[2]);
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    double c = atof(argv[5]);

    if (a <= 0 || b <= 0 || c <= 0){
        printf("Длины сторон треугольника должны быть положительными\n");
        exit(1);
    }
    
    int right = 0;

    if (fabs(a*a + b*b - c*c) < epsilon) right = 1;
    else if (fabs(a*a + c*c - b*b) < epsilon) right = 1;
    else if (fabs(c*c + b*b - a*a) < epsilon) right = 1;

    if (right){
        printf("Треугольник правильный\n");
    } else {
        printf("треугольник нерпавильный\n");
    }
}

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Ошибка, не указан флаг, либо указан неправилно\n");
        return 1;
    }

    char *flag = argv[1];

    if(flag[0] == '-' || flag[0] == '/'){
        if (flag[1] == 'q' && flag[2] == '\0'){
            handle_q_flag(argc, argv);
        }
        else if (flag[1] == 'm' && flag[2] == '\0'){
            handle_m_flag(argc, argv);
        }
        else if (flag[1] == 't' && flag[2] == '\0'){
            handle_t_flag(argc, argv);
        }
        else {
            printf("Неизвестный флаг\n");
        }
    }  
    else {
        printf("ошибка флага\n");
        return 1;
    }
    return 0;
}