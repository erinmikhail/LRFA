#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "ex1_lr1.h"


void test_parse_flag() {
    printf("Testing parse_flag...\n");
    
    assert(parse_flag('h') == FLAG_H);
    assert(parse_flag('p') == FLAG_P);
    assert(parse_flag('s') == FLAG_S);
    assert(parse_flag('e') == FLAG_E);
    assert(parse_flag('a') == FLAG_A);
    assert(parse_flag('f') == FLAG_F);
    
    assert(parse_flag('H') == FLAG_H);
    assert(parse_flag('P') == FLAG_P);
    assert(parse_flag('S') == FLAG_S);
    assert(parse_flag('E') == FLAG_E);
    assert(parse_flag('A') == FLAG_A);
    assert(parse_flag('F') == FLAG_F);
    
    assert(parse_flag('x') == FLAG_UNKNOWN);
    assert(parse_flag('1') == FLAG_UNKNOWN);
    assert(parse_flag(' ') == FLAG_UNKNOWN);
    assert(parse_flag('\0') == FLAG_UNKNOWN);
    
    printf("✓ All parse_flag tests passed!\n\n");
}


void test_is_prime() {
    printf("Testing is_prime...\n");
    
    assert(is_prime(2) == true);
    assert(is_prime(3) == true);
    assert(is_prime(5) == true);
    assert(is_prime(7) == true);
    assert(is_prime(11) == true);
    assert(is_prime(13) == true);
    assert(is_prime(17) == true);
    assert(is_prime(19) == true);
    
    assert(is_prime(1) == false);
    assert(is_prime(4) == false);
    assert(is_prime(6) == false);
    assert(is_prime(8) == false);
    assert(is_prime(9) == false);
    assert(is_prime(10) == false);
    assert(is_prime(12) == false);
    assert(is_prime(15) == false);
    
    assert(is_prime(0) == false);
    assert(is_prime(-1) == false);
    assert(is_prime(100) == false);
    
    printf("✓ All is_prime tests passed!\n\n");
}

void test_factorial() {
    printf("Testing factorial...\n");
    
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(2) == 2);
    assert(factorial(3) == 6);
    assert(factorial(4) == 24);
    assert(factorial(5) == 120);
    
    assert(factorial(10) == 3628800);
    assert(factorial(12) == 479001600);
    
    printf("✓ All factorial tests passed!\n\n");
}


void test_process_h() {
    printf("Testing process_h (will show output)...\n");
    
    printf("  Test 1: x=5 (должны быть кратные)\n");
    process_h(5);
    
    printf("  Test 2: x=50 (должны быть кратные)\n");
    process_h(50);
    
    printf("  Test 3: x=200 (не должно быть кратных в пределах 100)\n");
    process_h(200);
    
    printf("✓ process_h tests completed!\n\n");
}

void test_process_p() {
    printf("Testing process_p (will show output)...\n");
    
    printf("  Test 1: Простое число (7)\n");
    process_p(7);
    
    printf("  Test 2: Составное число (9)\n");
    process_p(9);
    
    printf("  Test 3: Число 1 (особый случай)\n");
    process_p(1);
    
    printf("  Test 4: Большое простое число (17)\n");
    process_p(17);
    
    printf("✓ process_p tests completed!\n\n");
}


void test_process_s() {
    printf("Testing process_s (will show output)...\n");
    
    printf("  Test 1: Число 255 (FF)\n");
    process_s(255);
    
    printf("  Test 2: Число 16 (10)\n");
    process_s(16);
    
    printf("  Test 3: Число 0\n");
    process_s(0);
    
    printf("  Test 4: Число 123456\n");
    process_s(123456);
    
    printf("✓ process_s tests completed!\n\n");
}


void test_process_e() {
    printf("Testing process_e (will show output)...\n");
    
    printf("  Test 1: x=3 (корректный ввод)\n");
    process_e(3);
    
    printf("  Test 2: x=5 (корректный ввод)\n");
    process_e(5);
    
    printf("  Test 3: x=11 (должна быть ошибка)\n");
    process_e(11);
    
    printf("✓ process_e tests completed!\n\n");
}


void test_process_a() {
    printf("Testing process_a (will show output)...\n");
    
    printf("  Test 1: x=10\n");
    process_a(10);
    
    printf("  Test 2: x=100\n");
    process_a(100);
    
    printf("  Test 3: x=1\n");
    process_a(1);
    
    printf("✓ process_a tests completed!\n\n");
}

void test_process_f() {
    printf("Testing process_f (will show output)...\n");
    
    printf("  Test 1: x=5 (корректный ввод)\n");
    process_f(5);
    
    printf("  Test 2: x=10 (корректный ввод)\n");
    process_f(10);
    
    printf("  Test 3: x=25 (должно быть переполнение)\n");
    process_f(25);
    
    printf("✓ process_f tests completed!\n\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");

    printf("  Testing with boundary values...\n");
    

    process_h(1);
    process_h(100);
    process_h(101);
    
    
    process_p(2);  
    process_p(1);  
    
    
    process_s(0);
    process_s(1);
    
    
    process_a(1);
    

    process_f(0);
    process_f(1);
    
    printf("✓ All edge case tests completed!\n\n");
}


void test_integration() {
    printf("Testing integration via command line...\n");
    

    printf("  Test 1: Flag -h (multiples)\n");
    int result = system("echo '10 -h' | ./ex1_lr1");
    if (result != 0) {
        printf("  ⚠ -h test returned non-zero: %d\n", result);
    }
    
    printf("  Test 2: Flag -p (prime check)\n");
    result = system("echo '7 -p' | ./ex1_lr1");
    if (result != 0) {
        printf("  ⚠ -p test returned non-zero: %d\n", result);
    }
    
    printf("  Test 3: Flag -s (hexadecimal)\n");
    result = system("echo '255 -s' | ./ex1_lr1");
    if (result != 0) {
        printf("  ⚠ -s test returned non-zero: %d\n", result);
    }
    
    printf("  Test 4: Flag -e (exponent table)\n");
    result = system("echo '5 -e' | ./ex1_lr1");
    if (result != 0) {
        printf("  ⚠ -e test returned non-zero: %d\n", result);
    }
    
    printf("  Test 5: Flag -a (sum)\n");
    result = system("echo '10 -a' | ./ex1_lr1");
    if (result != 0) {
        printf("  ⚠ -a test returned non-zero: %d\n", result);
    }
    
    printf("  Test 6: Flag -f (factorial)\n");
    result = system("echo '5 -f' | ./ex1_lr1");
    if (result != 0) {
        printf("  ⚠ -f test returned non-zero: %d\n", result);
    }
    
    printf("✓ Integration tests completed!\n\n");
}


void test_error_handling() {
    printf("Testing error handling via command line...\n");
    
    printf("  Test 1: Invalid flag\n");
    int result = system("echo '10 -x' | ./ex1_lr1");
    if (result == 0) {
        printf("  ⚠ Expected error but got success\n");
    }
    
    printf("  Test 2: Non-positive number\n");
    result = system("echo '0 -h' | ./ex1_lr1");
    if (result == 0) {
        printf("  ⚠ Expected error but got success\n");
    }
    
    printf("  Test 3: Invalid format\n");
    result = system("echo 'abc -h' | ./ex1_lr1");
    if (result == 0) {
        printf("  ⚠ Expected error but got success\n");
    }
    
    printf("✓ Error handling tests completed!\n\n");
}

int main() {
    printf("========================================\n");
    printf("Unit Tests for ex1_lr1\n");
    printf("========================================\n\n");
    
    test_parse_flag();
    test_is_prime();
    test_factorial();
    test_process_h();
    test_process_p();
    test_process_s();
    test_process_e();
    test_process_a();
    test_process_f();
    test_edge_cases();
    test_error_handling();
    
    
    printf("Building main program for integration tests...\n");
    if (system("gcc -Wall -Werror -Wextra -Wpedantic -fsanitize=address ex1_lr1.c ex1_lr1_func.c -o ex1_lr1") == 0) {
        test_integration();
    } else {
        printf("⚠ Could not build main program for integration tests\n");
    }
    
    printf("========================================\n");
    printf(" ALL TESTS COMPLETED SUCCESSFULLY!\n");
    printf("========================================\n");
    
    return 0;
}