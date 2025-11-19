#include <stdio.h>
#include <assert.h>
#include "brackets.h"

int main() {
    assert(check_brackets("()") == 1);
    assert(check_brackets("([])") == 1);
    assert(check_brackets("") == 1);
    assert(check_brackets("a + b") == 1);
    
    assert(check_brackets("(") == 0);
    assert(check_brackets(")") == 0);
    assert(check_brackets("([)]") == 0);
    
    printf("Все тесты пройдены!\n");
    return 0;
}