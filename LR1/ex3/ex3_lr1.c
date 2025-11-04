#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex3_lr1.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Ошибка: не указан флаг\n");
        printf("Использование:\n");
        printf("  -q epsilon a b c  - квадратные уравнения\n");
        printf("  -m num1 num2      - проверка кратности\n");
        printf("  -t epsilon a b c  - проверка треугольника\n");
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
            printf("Неизвестный флаг: %s\n", flag);
            printf("Доступные флаги: -q, -m, -t\n");
            return 1;
        }
    } else {
        printf("Ошибка: флаг должен начинаться с '-' или '/'\n");
        return 1;
    }
    
    return 0;
}