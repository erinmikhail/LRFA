#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex1_lr1.h"

int main() {
    int x;
    char flag[3];
    char action;

    printf("Введите число и флаг: ");


    if (scanf("%d", &x) != 1) {
        printf("Ошибка ввода числа\n");
        while (getchar() != '\n');
        return 1;
    }


    if (scanf("%2s", flag) != 1) {
        printf("Ошибка ввода флага\n");
        return 1;
    }


    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}


    if ((flag[0] != '-' && flag[0] != '/') || strlen(flag) != 2) {
        printf("Некорректный флаг\n");
        return 1;
    }


    if (x <= 0) {
        printf("Число должно быть натуральным\n");
        return 1;
    }

    action = flag[1];

    switch (action) {
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