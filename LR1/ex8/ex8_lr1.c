#include "ex8_lr1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error_message(StatusCode code) {
    switch (code) {
        case ERROR_INVALID_BASE:
            printf("Error: Invalid base! Must be between 2 and 36.\n");
            break;
        case ERROR_INVALID_CHARACTER:
            printf("Error: Invalid character in number!\n");
            break;
        case ERROR_EMPTY_INPUT:
            printf("Error: Empty input!\n");
            break;
        case ERROR_READING_INPUT:
            printf("Error: Reading input failed!\n");
            break;
        case ERROR_CONVERSION:
            printf("Error: Conversion failed!\n");
            break;
        default:
            printf("Error: Unknown error occurred!\n");
            break;
    }
}

StatusCode find_max_absolute(void) {
    int base;
    char buffer[BUFFER_SIZE];
    Number max_number = {"", 0, 0};
    int numbers_count = 0;
    
    printf("Enter base (2-36): ");
    if (scanf("%d", &base) != 1) {
        return ERROR_READING_INPUT;
    }
    
    if (base < MIN_BASE || base > MAX_BASE) {
        return ERROR_INVALID_BASE;
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Enter numbers (type 'Stop' to finish):\n");
    
    while (1) {
        printf("> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        if (strcmp(buffer, "Stop") == 0) {
            break;
        }
        
        if (buffer[0] == '\0') {
            continue;
        }
        
        StatusCode validation_status = validate_number(buffer, base);
        if (validation_status != SUCCESS) {
            print_error_message(validation_status);
            continue;
        }
        
        long long current_value = str_to_base10(buffer, base);
        long long current_abs_value = llabs(current_value);
        long long max_abs_value = llabs(max_number.decimal_value);
        
        if (numbers_count == 0 || current_abs_value > max_abs_value) {
            strcpy(max_number.original_str, buffer);
            max_number.decimal_value = current_value;
            max_number.original_base = base;
        }
        
        numbers_count++;
    }
    
    if (numbers_count > 0) {
        printf("\nMaximum absolute value: ");
        remove_leading_zeros(max_number.original_str);
        printf("%s\n", max_number.original_str);
        printf("In different bases:\n");
        
        int output_bases[OUTPUT_BASES_COUNT] = {9, 18, 27, 36};
        char result[BUFFER_SIZE];
        
        for (int i = 0; i < OUTPUT_BASES_COUNT; i++) {
            StatusCode conversion_status = convert_base_to_base(
                max_number.original_str,
                max_number.original_base, 
                output_bases[i], 
                result
            );
            
            if (conversion_status == SUCCESS) {
                remove_leading_zeros(result);
                printf("Base %2d: %s\n", output_bases[i], result);
            } else {
                printf("Base %2d: Conversion error\n", output_bases[i]);
            }
        }
        
        return SUCCESS;
    } else {
        printf("No valid numbers entered.\n");
        return ERROR_EMPTY_INPUT;
    }
}

int main() {
    StatusCode result = find_max_absolute();
    
    if (result != SUCCESS) {
        print_error_message(result);
        return result;
    }
    
    return SUCCESS;
}