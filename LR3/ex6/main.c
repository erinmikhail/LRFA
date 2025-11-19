#include <stdio.h>
#include "brackets.h"

int main() {
    char expression[1000];

    printf("введите выражениеЖ ");
    scanf("%s", expression);

    if (check_brackets(expression)){
        printf("все гуд\n");
    } else{
        printf("Все хреново\n");
    }
}