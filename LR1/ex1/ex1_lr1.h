#ifndef EX1_LR1_H
#define EX1_LR1_H

#include <stdbool.h>


typedef enum {
    FLAG_H,      // Кратные числа
    FLAG_P,      // Проверка на простое число
    FLAG_S,      // Шестнадцатеричное представление
    FLAG_E,      // Таблица степеней
    FLAG_A,      // Сумма чисел
    FLAG_F,      // Факториал
    FLAG_UNKNOWN // Неизвестный флаг
} CommandFlag;

void process_h(int x);
void process_p(int x);
void process_s(int x);
void process_e(int x);
void process_a(int x);
void process_f(int x);
bool is_prime(int n);
long long factorial(int n);
CommandFlag parse_flag(char flag_char);

#endif