#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/interpreter.h"

void test_variables() {
    printf("Testing variables...\n");
    init_interpreter();
    
    set_variable_value('A', 5);
    assert(get_variable_value('A') == 5);
    printf("✓ Set and get variable A\n");
    
    set_variable_value('Z', 100);
    assert(get_variable_value('Z') == 100);
    printf("✓ Set and get variable Z\n");
    
    char state[512];
    get_variables_state(state, sizeof(state));
    printf("✓ Variables state: %s\n", state);
    
    cleanup_interpreter();
}

void test_assignment() {
    printf("\nTesting assignment...\n");
    init_interpreter();
    
    char op_desc[50];
    int result = execute_line("A = 5", op_desc);
    assert(result == 5);
    assert(strcmp(op_desc, "Assignment") == 0);
    assert(get_variable_value('A') == 5);
    printf("✓ Simple assignment A = 5\n");
    
    result = execute_line("B = 10 + 2", op_desc);
    assert(result == 12);
    assert(get_variable_value('B') == 12);
    printf("✓ Assignment with expression B = 10 + 2\n");
    
    cleanup_interpreter();
}

void test_arithmetic() {
    printf("\nTesting arithmetic operations...\n");
    init_interpreter();
    
    char op_desc[50];
    execute_line("A = 6", op_desc);
    execute_line("B = 3", op_desc);
    
    int result = execute_line("C = A + B * 2", op_desc);
    assert(result == 12);
    printf("✓ Addition and multiplication: 6 + 3 * 2 = %d\n", result);
    
    result = execute_line("D = A - B", op_desc);
    assert(result == 3);
    printf("✓ Subtraction: 6 - 3 = %d\n", result);
    
    result = execute_line("E = A * B", op_desc);
    assert(result == 18);
    printf("✓ Multiplication: 6 * 3 = %d\n", result);
    
    result = execute_line("F = A / B", op_desc);
    assert(result == 2);
    printf("✓ Division: 6 / 3 = %d\n", result);
    
    cleanup_interpreter();
}

void test_exponentiation() {
    printf("\nTesting exponentiation...\n");
    init_interpreter();
    
    char op_desc[50];
    execute_line("A = 2", op_desc);
    execute_line("B = 3", op_desc);
    
    int result = execute_line("C = A ^ B", op_desc);
    assert(result == 8);
    printf("✓ Exponentiation: 2 ^ 3 = %d\n", result);
    
    result = execute_line("D = 5 ^ 2", op_desc);
    assert(result == 25);
    printf("✓ Exponentiation: 5 ^ 2 = %d\n", result);
    
    cleanup_interpreter();
}

void test_complex_expression() {
    printf("\nTesting complex expression...\n");
    init_interpreter();
    
    char op_desc[50];
    execute_line("A = 2", op_desc);
    execute_line("B = 3", op_desc);
    execute_line("C = 4", op_desc);
    
    int result = execute_line("D = A + B * C ^ 2", op_desc);
    assert(result == 50); // 2 + 3 * 4^2 = 2 + 3*16 = 2 + 48 = 50
    printf("✓ Complex expression: 2 + 3 * 4 ^ 2 = %d\n", result);
    
    cleanup_interpreter();
}

void test_print() {
    printf("\nTesting print function...\n");
    init_interpreter();
    
    char op_desc[50];
    execute_line("A = 42", op_desc);
    
    printf("Expected output: 42\n");
    printf("Actual output: ");
    int result = execute_line("print(A)", op_desc);
    assert(result == 42);
    assert(strcmp(op_desc, "Print A") == 0);
    printf("✓ Print function works\n");
    
    cleanup_interpreter();
}

int main() {
    printf("Running interpreter tests...\n\n");
    
    test_variables();
    test_assignment();
    test_arithmetic();
    test_exponentiation();
    test_complex_expression();
    test_print();
    
    printf("\n🎉 All tests passed!\n");
    return 0;
}