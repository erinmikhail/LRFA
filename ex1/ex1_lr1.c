#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex1_lr1.h"

int main(){
    char input[50];
    int x;
    char flag[3];
    char action;

    printf("Введите число и флаг: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Ошибка ввода\n");
        return 1;
    } 
    
    if (sscanf(input, "%d %2s", &x, flag) != 2) {
        printf("Неверный формат ввода\n");
        return 1;
    } 
    
    if ((flag[0] != '-' && flag[0] != '/') || strlen(flag) != 2){
        printf("Некорректный флаг\n");
        return 1;
    } 
    
    if (x <= 0) {
        printf("Число должно быть натуральным\n");
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