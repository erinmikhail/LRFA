#include <stdio.h>
#include <stdlib.h>
#include "ex2_lr1.h"

int main() {
    int T;
    
    printf("Введите количество запросов: ");
    if (scanf("%d", &T) != 1 || T <= 0) {
        printf("Ошибка: неверное количество запросов\n");
        return 1;
    }
    
    int *queries = malloc(T * sizeof(*queries));
    if (!queries) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    
    int max_n = 0;
    printf("Введите %d чисел (по одному в строке):\n", T);
    
    for (int i = 0; i < T; i++) {
        if (scanf("%d", &queries[i]) != 1) {
            printf("Ошибка ввода числа\n");
            free(queries);
            return 1;
        }
        if (queries[i] <= 0) {
            printf("Ошибка: номер простого числа должен быть положительным\n");
            free(queries);
            return 1;
        }
        if (queries[i] > max_n) {
            max_n = queries[i];
        }
    }
    
    int* primes = find_primes(max_n);
    if (!primes) {
        printf("Ошибка: не удалось найти простые числа\n");
        free(queries);
        return 1;
    }
    
    printf("\nРезультаты:\n");
    for (int i = 0; i < T; i++) {
        printf("%d-е простое число: %d\n", queries[i], primes[queries[i] - 1]);
    }
    
    free(queries);
    free(primes);
    
    return 0;
}