#include <stdio.h>
#include "brackets.h"

int main() {
    const char *test[] = {
        "(a + b)",
        "([{<>}])",
        "((())",
        "())", 
        "([)]",
        "a + b",
        ""
    };

    for (int i = 0; i < 7; i++){
        printf("Строка: \"%s\"\n", test[i]);
        printf("рез: %s\n\n", check_brackets(test[i]) ? "OK" : "ERROR");
    }

    return 0;
}