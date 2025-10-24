#include "include.h"


char* int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    static const char* roman_numerals[] = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    static const int values[] = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    
    char* result = malloc(50);
    result[0] = '\0';
    
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            strcat(result, roman_numerals[i]);
            num -= values[i];
        }
    }
    
    return result;
}


static void generate_fibonacci(unsigned int limit, unsigned int* fib, int* count) {
    fib[0] = 1;
    fib[1] = 2;
    *count = 2;
    
    while (fib[*count - 1] <= limit) {
        fib[*count] = fib[*count - 1] + fib[*count - 2];
        (*count)++;
    }
}


char* zeckendorf_representation(unsigned int num) {
    if (num == 0) {
        char* result = malloc(3);
        strcpy(result, "01");
        return result;
    }
    
    unsigned int fib[50];
    int fib_count;
    generate_fibonacci(num, fib, &fib_count);
    

    int coefficients[50] = {0};
    unsigned int temp = num;
    
    for (int i = fib_count - 1; i >= 0; i--) {
        if (temp >= fib[i]) {
            coefficients[i] = 1;
            temp -= fib[i];
        }
    }
    

    char* result = malloc(100);
    int pos = 0;
    
    for (int i = 0; i < fib_count; i++) {
        result[pos++] = coefficients[i] + '0';
    }
    result[pos++] = '1'; // Дополнительная единица в конце
    result[pos] = '\0';
    
    return result;
}

int is_valid_base(int base) {
    return base >= 2 && base <= 36;
}


char* int_to_base(int num, int base, int uppercase) {
    if (!is_valid_base(base)) base = 10;
    
    char* result = malloc(100);
    char* ptr = result;
    int is_negative = 0;
    long long n = num;
    
    if (n < 0) {
        is_negative = 1;
        n = -n;
    }
    
    do {
        int digit = n % base;
        if (digit < 10) {
            *ptr++ = digit + '0';
        } else {
            *ptr++ = (uppercase ? 'A' : 'a') + (digit - 10);
        }
        n /= base;
    } while (n > 0);
    
    if (is_negative) {
        *ptr++ = '-';
    }
    
    *ptr = '\0';

    int len = strlen(result);
    for (int i = 0; i < len / 2; i++) {
        char temp = result[i];
        result[i] = result[len - 1 - i];
        result[len - 1 - i] = temp;
    }
    
    return result;
}


long long str_to_int_base(const char *str, int base, int uppercase) {
    if (!is_valid_base(base)) base = 10;
    
    long long result = 0;
    int is_negative = 0;
    const char* ptr = str;

    while (*ptr == ' ') ptr++;
    

    if (*ptr == '-') {
        is_negative = 1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }
    

    while (*ptr) {
        char c = *ptr;
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z' && !uppercase) {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z' && uppercase) {
            digit = c - 'A' + 10;
        } else {
            break;
        }
        
        if (digit >= base) break;
        
        result = result * base + digit;
        ptr++;
    }
    
    return is_negative ? -result : result;
}


char* byte_to_binary(unsigned char byte) {
    char* result = malloc(9);
    for (int i = 7; i >= 0; i--) {
        result[7 - i] = (byte & (1 << i)) ? '1' : '0';
    }
    result[8] = '\0';
    return result;
}


char* memory_dump_int(int value) {
    unsigned char* bytes = (unsigned char*)&value;
    char* result = malloc(100);
    result[0] = '\0';
    
    for (int i = 0; i < 4; i++) {
        char* binary = byte_to_binary(bytes[i]);
        strcat(result, binary);
        if (i < 3) strcat(result, " ");
        free(binary);
    }
    
    return result;
}


char* memory_dump_uint(unsigned int value) {
    return memory_dump_int(*(int*)&value);
}


char* memory_dump_double(double value) {
    unsigned char* bytes = (unsigned char*)&value;
    char* result = malloc(200);
    result[0] = '\0';
    
    for (int i = 0; i < 8; i++) {
        char* binary = byte_to_binary(bytes[i]);
        strcat(result, binary);
        if (i < 7) strcat(result, " ");
        free(binary);
    }
    
    return result;
}


char* memory_dump_float(float value) {
    unsigned char* bytes = (unsigned char*)&value;
    char* result = malloc(100);
    result[0] = '\0';
    
    for (int i = 0; i < 4; i++) {
        char* binary = byte_to_binary(bytes[i]);
        strcat(result, binary);
        if (i < 3) strcat(result, " ");
        free(binary);
    }
    
    return result;
}


static int process_format_specifier(FILE* stream, char* str, const char** format, va_list* args, int is_sprintf) {
    const char* fmt = *format;
    fmt++; // Пропускаем '%'
    

    if (strncmp(fmt, "Ro", 2) == 0) {
        int num = va_arg(*args, int);
        char* roman = int_to_roman(num);
        int len = strlen(roman);
        if (is_sprintf) {
            strcpy(str, roman);
        } else {
            fputs(roman, stream);
        }
        free(roman);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "Zr", 2) == 0) {
        unsigned int num = va_arg(*args, unsigned int);
        char* zeck = zeckendorf_representation(num);
        int len = strlen(zeck);
        if (is_sprintf) {
            strcpy(str, zeck);
        } else {
            fputs(zeck, stream);
        }
        free(zeck);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "Cv", 2) == 0) {
        int num = va_arg(*args, int);
        int base = va_arg(*args, int);
        char* converted = int_to_base(num, base, 0);
        int len = strlen(converted);
        if (is_sprintf) {
            strcpy(str, converted);
        } else {
            fputs(converted, stream);
        }
        free(converted);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "CV", 2) == 0) {
        int num = va_arg(*args, int);
        int base = va_arg(*args, int);
        char* converted = int_to_base(num, base, 1);
        int len = strlen(converted);
        if (is_sprintf) {
            strcpy(str, converted);
        } else {
            fputs(converted, stream);
        }
        free(converted);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "to", 2) == 0) {
        const char* num_str = va_arg(*args, const char*);
        int base = va_arg(*args, int);
        long long result = str_to_int_base(num_str, base, 0);
        
        char buffer[50];
        sprintf(buffer, "%lld", result);
        int len = strlen(buffer);
        if (is_sprintf) {
            strcpy(str, buffer);
        } else {
            fputs(buffer, stream);
        }
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "TO", 2) == 0) {
        const char* num_str = va_arg(*args, const char*);
        int base = va_arg(*args, int);
        long long result = str_to_int_base(num_str, base, 1);
        
        char buffer[50];
        sprintf(buffer, "%lld", result);
        int len = strlen(buffer);
        if (is_sprintf) {
            strcpy(str, buffer);
        } else {
            fputs(buffer, stream);
        }
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "mi", 2) == 0) {
        int num = va_arg(*args, int);
        char* dump = memory_dump_int(num);
        int len = strlen(dump);
        if (is_sprintf) {
            strcpy(str, dump);
        } else {
            fputs(dump, stream);
        }
        free(dump);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "mu", 2) == 0) {
        unsigned int num = va_arg(*args, unsigned int);
        char* dump = memory_dump_uint(num);
        int len = strlen(dump);
        if (is_sprintf) {
            strcpy(str, dump);
        } else {
            fputs(dump, stream);
        }
        free(dump);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "md", 2) == 0) {
        double num = va_arg(*args, double);
        char* dump = memory_dump_double(num);
        int len = strlen(dump);
        if (is_sprintf) {
            strcpy(str, dump);
        } else {
            fputs(dump, stream);
        }
        free(dump);
        *format = fmt + 2;
        return len;
    }
    else if (strncmp(fmt, "mf", 2) == 0) {
        float num = va_arg(*args, double); 
        char* dump = memory_dump_float(num);
        int len = strlen(dump);
        if (is_sprintf) {
            strcpy(str, dump);
        } else {
            fputs(dump, stream);
        }
        free(dump);
        *format = fmt + 2;
        return len;
    }

    char specifier[3] = { '%', *fmt, '\0' };
    *format = fmt + 1;
    
    if (is_sprintf) {
        return vsprintf(str, specifier, *args);
    } else {
        return vfprintf(stream, specifier, *args);
    }
}

int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int total_chars = 0;
    const char* ptr = format;
    
    while (*ptr) {
        if (*ptr == '%') {
            char buffer[1000];
            int chars_written = process_format_specifier(stream, buffer, &ptr, &args, 0);
            total_chars += chars_written;
        } else {
            fputc(*ptr, stream);
            total_chars++;
            ptr++;
        }
    }
    
    va_end(args);
    return total_chars;
}


int oversprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int total_chars = 0;
    const char* ptr = format;
    char* output_ptr = str;
    
    while (*ptr) {
        if (*ptr == '%') {
            char buffer[1000];
            int chars_written = process_format_specifier(NULL, buffer, &ptr, &args, 1);
            strcpy(output_ptr, buffer);
            output_ptr += chars_written;
            total_chars += chars_written;
        } else {
            *output_ptr++ = *ptr;
            total_chars++;
            ptr++;
        }
    }
    
    *output_ptr = '\0';
    va_end(args);
    return total_chars;
}