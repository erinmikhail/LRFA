#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ex1_lr1.h"

CommandFlag parse_flag(char flag_char) {
    switch (flag_char) {
        case 'h': case 'H': return FLAG_H;
        case 'p': case 'P': return FLAG_P;
        case 's': case 'S': return FLAG_S;
        case 'e': case 'E': return FLAG_E;
        case 'a': case 'A': return FLAG_A;
        case 'f': case 'F': return FLAG_F;
        default: return FLAG_UNKNOWN;
    }
}

void process_h(int x){
    printf("Числа кратные %d в пределах 100:\n", x);

    bool found = false;

    for (int i = x; i <= 100; i += x){
        printf("%d ", i);
        found = true;
    }

    if (!found){
        printf("Таких чисел нет");
    } else {
        printf("\n");
    }
}

void process_p(int x){
    if (x == 1){
        printf("Цифра 1 не является простой или составной\n");
        return;
    }

    if (is_prime(x)){
        printf("Число %d является простым\n", x);
    } else {
        printf("Число %d является составным\n", x);
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
    int cop = x;
    
    while (cop > 0) {
        int digit = cop % 16;
        cop = cop / 16;
        
        if (digit < 10) {
            digits[count] = '0' + digit;
        } else {
            digits[count] = 'A' + (digit - 10);
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
        printf("Ошибка, слишком высокая степень\n");
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
        printf("Переполнение\n");
        return;
    }

    long long result = factorial(x);
    printf("Факториал %d: %lld\n", x, result);
}

bool is_prime(int n){
    if (n <= 1) return false;
    if (n <= 3) return true;
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