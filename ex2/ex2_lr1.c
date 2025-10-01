#include <stdio.h>
#include <stdlib.h>


int* find_primes(int max_count) {
    if (max_count <= 0) return NULL;
    
    int limit;
    if (max_count < 100) {
        limit = 1000;  //  100 простых чисел
    } else if (max_count < 1000) {
        limit = 10000; //  1000 простых чисел
    } else {
        limit = max_count * 20; 
    }
    
    // Создаём массив для решета
    char* is_prime = (char*)malloc((limit + 1) * sizeof(char));
    int* primes = (int*)malloc(max_count * sizeof(int));
    
    // Инициализация решета
    for (int i = 0; i <= limit; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    
    // Решето Эратосфена
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

int main() {



    int T;

    printf("Введите кол-во чисел, которые будет вводить, а потом каждое число через enter: \n");

    scanf("%d", &T);
    
    int *queries = malloc(T * sizeof(*queries));
    int max_n = 0;
    
    for (int i = 0; i < T; i++) {
        scanf("%d", &queries[i]);
        if (queries[i] > max_n) {
            max_n = queries[i];
        }
    }
    
    int* primes = find_primes(max_n);
    
    printf("Вывод: \n");
    for (int i = 0; i < T; i++) {
        printf("%d\n", primes[queries[i] - 1]); // -1 так как индексация с 0
    }
    
    free(queries);
    free(primes);
    
    return 0;
}