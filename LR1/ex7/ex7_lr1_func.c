#include "ex7_lr1.h"
#include <string.h>


int char_to_value(char c){
    if (c >= '0' && c <= '9'){
        return c - '0';
    } else if (c >= 'A' && c <= 'Z'){
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'z'){
        return c - 'a' + 10;
    } else {
        return INVALID_CHAR_VALUE;
    }
}



int min_base(const char *num_str) {
    int max_digit = 0;
    for (const char *p = num_str; *p; p++) {
        int val = char_to_value(*p);
        if (val == INVALID_CHAR_VALUE) {
            return INVALID_CHAR_VALUE;
        }
        if (val > max_digit)
            max_digit = val;
    }
    

    int base = (max_digit < MIN_BASE) ? MIN_BASE : (max_digit + 1);
    
    if (base < MIN_BASE || base > MAX_BASE) {
        return INVALID_CHAR_VALUE;
    }
    
    return base;
}


StatusCode str_to_base10(const char *num_str, int base, long long *result) {
    *result = 0;
    

    if (base < MIN_BASE || base > MAX_BASE) {
        return ERROR_INVALID_CHARACTER;
    }
    
    for (const char *p = num_str; *p; p++) {
        int digit_value = char_to_value(*p);
        

        if (digit_value == INVALID_CHAR_VALUE || digit_value >= base) {
            return ERROR_INVALID_CHARACTER;
        }
        

        long long new_result = (*result) * base + digit_value;
        if (new_result < *result) {  
            return ERROR_INVALID_CHARACTER;
        }
        
        *result = new_result;
    }
    
    return SUCCESS;
}


void remove_leading_zeros(char *str) {
    char *dst = str;
    char *src = str;
    

    while (*src == '0' && *(src + 1) != '\0')
        src++;
    

    while (*src) {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}


StatusCode process_number(const char *input, char *output, int *base, long long *decimal) {

    char processed_num[BUFFER_SIZE];
    

    if (strlen(input) >= BUFFER_SIZE) {
        return ERROR_INVALID_CHARACTER;
    }
    
    strcpy(processed_num, input);
    

    remove_leading_zeros(processed_num);
    

    if (processed_num[0] == '\0') {
        strcpy(processed_num, "0");
    }
    

    *base = min_base(processed_num);
    if (*base == INVALID_CHAR_VALUE) {
        return ERROR_INVALID_CHARACTER;
    }
    

    StatusCode status = str_to_base10(processed_num, *base, decimal);
    if (status != SUCCESS) {
        return status;
    }
    

    strcpy(output, processed_num);
    
    return SUCCESS;
}


StatusCode process_file(FILE *fin, FILE *fout) {
    char buffer[BUFFER_SIZE];
    char processed_num[BUFFER_SIZE];
    int base;
    long long decimal;
    StatusCode status;
    
    while (fscanf(fin, "%255s", buffer) == 1) {
        status = process_number(buffer, processed_num, &base, &decimal);
        
        if (status != SUCCESS) {
            fprintf(stderr, "Error processing number: %s\n", buffer);

            fprintf(fout, "%s ERROR %d\n", buffer, status);
            continue; 
        }
        

        fprintf(fout, "%s %d %lld\n", processed_num, base, decimal);
    }
    

    if (ferror(fin)) {
        return ERROR_READING_FILE;
    }
    
    return SUCCESS;
}