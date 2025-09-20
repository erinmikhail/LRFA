#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void process_h(int x);
void process_p(int x);
void process_s(int x);
void process_e(int x);
void process_a(int x);
void process_f(int x);
bool is_prime(int n);
long long factorial(int n);

void process_h(int x){
    printf("Числа кратные %d в предлеах 100:\n", x);

    bool found = false;

    for (int i = x; i <= 100; i += x){
        printf("%d ", i);
        found = true;
    }

    if (!found){
        printf("Таких числе нет");
    } else {
        printf("\n");
    }
}


void process_p(int x){
    if (x == 1){
        printf("Цифра 1 не явл прост или сост");
        return;
    }

    if (is_prime(x) == true){
        printf("Число %d является простым", x);
    } else {
        printf("Число %d явл сост", x);
    }
}


void process_s(int x) {
    printf("Шестнадцатеричные цифры числа %d: ", x);
    
    if (x == 0) {
        printf("0\n");
        return;
    }
    
    char digits[20];
    int count = 0;
    int temp = x;
    
    while (temp > 0) {
        int digit = temp % 16;
        temp = temp / 16;
        
        if (digit < 10) {
            digits[count] = '0' + digit;  // цифры 0-9
        } else {
            digits[count] = 'A' + (digit - 10);  // буквы A-F
        }
        count++;
    }
    

    for (int i = count - 1; i >= 0; i--) {
        printf("%c", digits[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
}


void process_e(int x){
    if (x > 10){
        printf("Ошибка, слишком высокая степень");
        return;
    }

    printf("Таблица степеней (основания 1-10, степени 1-%d):\n", x);
    printf("%6s", "Осн\\Степ");
    
    for (int i = 1; i <= x; i++) {
        printf("%8d", i);
    }
    printf("\n");
    
    for (int base = 1; base <= 10; base++) {
        printf("%6d", base);
        for (int exp = 1; exp <= x; exp++) {
            long result = 1;
            for (int i = 0; i < exp; i++) {
                result *= base;
            }
            printf("%8ld", result);
        }
        printf("\n");
    }
}


void process_a(int x){
    long sum = (long)x * (x + 1) / 2;
    printf("Сумма чисел от 1 до %d: %ld\n", x, sum);
}


void process_f(int x){
    if (x > 20){
        printf("переполнение");
    }

    long long result = factorial(x);
    printf("Факториал %lld\n", result);
}


bool is_prime(int n){
    if (n <= 1) return false;
    if (n > 1 && n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}


long long factorial(int n){
    if (n == 0 || n == 1) return 1;

    long long result = 1;
    for (int i = 2; i <= n; i++){
        result *= i;
    }

    return result;
}


int main(){
    char input[50];
    int x;
    char flag[3];
    char action;

    printf("Ввести число и флаг: ");


// проверка аргументов
    if (fgets(input, sizeof(input),stdin) == NULL) {
        printf("ошибка");
        return 1;
    } 
    
    if (sscanf(input, "%d %2s", &x, flag) != 2) {
        printf("Неверный формат");
        return 1;
    } 
    
    if ((flag[0] != '-' && flag[0] != '/') || strlen(flag) != 2){
        printf("Нет флага");
        return 1;
    } 
    
    if (x <= 0) {
        printf("Число не натуральное");
        return 1;
    } 
    
    action = flag[1];


    switch (action){
        case 'h': case 'H':
            process_h(x);
            break;
        case 'p': case 'P':
            process_p(x);
            break;
        case 's': case 'S':
            process_s(x);
            break;
        case 'e': case 'E':
            process_e(x);
            break;
        case 'a': case 'A':
            process_a(x);
            break;
        case 'f': case 'F':
            process_f(x);
            break;
        default:
            printf("Ошибка: неизвестный флаг '%s'\n", flag);
            printf("Доступные флаги: -h, -p, -s, -e, -a, -f\n");
            return 1;
    }

    return 0;
}