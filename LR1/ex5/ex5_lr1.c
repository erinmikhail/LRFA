#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ex5_lr1.h"

int main(int argc, char *argv[]) {
    if (!validate_arguments(argc, argv)) {
        return 1;
    }

    char *flag = argv[1];
    char *input_path = argv[2];
    char *output_path = NULL;  
    char action_flag;
    int has_n;

    if (!parse_flag(flag, &action_flag, &has_n)) {
        return 1;
    }

   
    output_path = malloc(256 * sizeof(char));
    if (!output_path) {
        printf("Ошибка: не удалось выделить память\n");
        return 1;
    }

    if (!create_output_path(output_path, input_path, has_n, argv)) {
        free(output_path);  
        return 1;
    }

    FILE *in = fopen(input_path, "r");
    if (!in) {
        printf("Ошибка: не удалось открыть файл %s\n", input_path);
        free(output_path);
        return 1;
    }

    FILE *out = fopen(output_path, "w");
    if (!out) {
        printf("Ошибка: не удалось создать файл %s\n", output_path);
        fclose(in);
        free(output_path);
        return 1;
    }

    int success = 1;
    switch (action_flag) {
        case 'd': 
            process_d(in, out);
            break;
        case 'i': 
            process_i(in, out);
            break;
        case 's': 
            process_s(in, out);
            break;
        case 'a': 
            process_a(in, out);
            break;
        default:
            printf("Неизвестный флаг '%c'\n", action_flag);
            printf("Доступные флаги: d, i, s, a\n");
            success = 0;
            break;
    }
    
    fclose(in);
    fclose(out);
    
    if (success) {
        printf("Обработка завершена успешно. Результат в файле: %s\n", output_path);
        free(output_path);  
        return 0;
    } else {
        remove(output_path); 
        free(output_path);   
        return 1;
    }
}