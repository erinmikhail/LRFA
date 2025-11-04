#include <stdio.h>
#include <stdlib.h>
#include "ex2_lr1.h"

int is_prime_simple(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

int* find_primes(int max_count) {
    if (max_count <= 0) return NULL;
    
    int limit;
    if (max_count < 100) {
        limit = 1000;  
    } else if (max_count < 1000) {
        limit = 10000; 
    } else {
        limit = max_count * 20;
    }
    

    char* is_prime = (char*)malloc((limit + 1) * sizeof(char));
    if (!is_prime) return NULL;
    
    int* primes = (int*)malloc(max_count * sizeof(int));
    if (!primes) {
        free(is_prime);
        return NULL;
    }
    

    for (int i = 0; i <= limit; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    

    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    

    int count = 0;
    for (int i = 2; i <= limit && count < max_count; i++) {
        if (is_prime[i]) {
            primes[count++] = i;
        }
    }
    
    free(is_prime);
    return primes;
}