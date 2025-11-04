#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "ex6_lr1.h"

// Простые функции для тестирования
double linear_func(double x) { return x; }

// Базовые тесты
void test_basic() {
    printf("Testing basic functionality...\n");
    
    // Тест подынтегральной функции
    assert(fabs(function_a(0.5) - log(1.5)/0.5) < 1e-10);
    printf("✓ function_a test passed\n");
    
    // Простой тест метода трапеций
    double result = trapezoidal_method(linear_func, 0, 1, 1e-6);
    assert(fabs(result - 0.5) < 1e-6);
    printf("✓ trapezoidal_method test passed\n");
    
    printf("✓ All basic tests passed!\n\n");
}

int main() {
    printf("========================================\n");
    printf ("Simple Unit Tests for ex6_lr1\n");
    printf("========================================\n\n");
    
    test_basic();
    
    printf("========================================\n");
    printf("✅ SIMPLE TESTS COMPLETED SUCCESSFULLY!\n");
    printf("========================================\n");
    
    return 0;
}