#include "include.h"

static int roman_char_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int roman_to_int(const char *roman) {
    int result = 0;
    int prev_value = 0;
    
    for (int i = strlen(roman) - 1; i >= 0; i--) {
        int value = roman_char_value(roman[i]);
        if (value < prev_value) {
            result -= value;
        } else {
            result += value;
        }
        prev_value = value;
    }
    return result;
}

static void generate_fibonacci(unsigned int limit, unsigned int* fib, int* count) {
    fib[0] = 1;
    fib[1] = 2;
    *count = 2;
    
    while (*count < 50 && fib[*count - 1] <= limit) {
        fib[*count] = fib[*count - 1] + fib[*count - 2];
        (*count)++;
    }
}

unsigned int zeckendorf_to_uint(const char *zeck) {
    int len = strlen(zeck);
    if (len < 2 || zeck[len - 1] != '1') return 0;
    
    unsigned int fib[50];
    int fib_count;
    generate_fibonacci(4294967295U, fib, &fib_count);
    
    unsigned int result = 0;
    for (int i = 0; i < len - 1; i++) {
        if (zeck[i] == '1') {
            if (i >= fib_count) return 0;
            result += fib[i];
        } else if (zeck[i] != '0') {
            return 0;
        }
    }
    return result;
}

int is_valid_base(int base) {
    return base >= 2 && base <= 36;
}

long long str_to_int_base_ptr(const char **str, int base, int uppercase) {
    if (!is_valid_base(base)) base = 10;
    
    const char *ptr = *str;
    long long result = 0;
    int is_negative = 0;
    
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
    
    *str = ptr;
    return is_negative ? -result : result;
}

static int process_input_specifier(FILE* stream, const char** str, const char** format, va_list* args, int is_sscanf) {
    const char* fmt = *format;
    fmt++;
    
    if (strncmp(fmt, "Ro", 2) == 0) {
        int* num_ptr = va_arg(*args, int*);
        char buffer[100] = {0};
        int i = 0;
        
        if (is_sscanf) {
            const char* s = *str;
            while (*s && (strchr("IVXLCDM", *s))) {
                buffer[i++] = *s++;
            }
            buffer[i] = '\0';
            *str = s;
        } else {
            while (i < 99) {
                int c = fgetc(stream);
                if (c == EOF || !strchr("IVXLCDM", c)) {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                buffer[i++] = c;
            }
            buffer[i] = '\0';
        }
        
        *num_ptr = roman_to_int(buffer);
        *format = fmt + 2;
        return i > 0 ? 1 : 0;
    }
    else if (strncmp(fmt, "Zr", 2) == 0) {
        unsigned int* num_ptr = va_arg(*args, unsigned int*);
        char buffer[100] = {0};
        int i = 0;
        
        if (is_sscanf) {
            const char* s = *str;
            while (*s && (*s == '0' || *s == '1')) {
                buffer[i++] = *s++;
            }
            if (*s == '1') {
                buffer[i++] = *s++;
            }
            buffer[i] = '\0';
            *str = s;
        } else {
            while (i < 99) {
                int c = fgetc(stream);
                if (c == EOF || (c != '0' && c != '1')) {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                buffer[i++] = c;
            }
            if (i > 0 && buffer[i-1] != '1') {
                int c = fgetc(stream);
                if (c == '1') {
                    buffer[i++] = c;
                } else if (c != EOF) {
                    ungetc(c, stream);
                }
            }
            buffer[i] = '\0';
        }
        
        *num_ptr = zeckendorf_to_uint(buffer);
        *format = fmt + 2;
        return i > 0 ? 1 : 0;
    }
    else if (strncmp(fmt, "Cv", 2) == 0) {
        int* num_ptr = va_arg(*args, int*);
        int base = va_arg(*args, int);
        
        if (is_sscanf) {
            long long result = str_to_int_base_ptr(str, base, 0);
            *num_ptr = (int)result;
        } else {
            char buffer[100] = {0};
            int i = 0;
            int c;
            
            while (i < 99) {
                c = fgetc(stream);
                if (c == EOF || isspace(c)) {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                buffer[i++] = c;
            }
            buffer[i] = '\0';
            
            const char* temp = buffer;
            long long result = str_to_int_base_ptr(&temp, base, 0);
            *num_ptr = (int)result;
        }
        
        *format = fmt + 2;
        return 1;
    }
    else if (strncmp(fmt, "CV", 2) == 0) {
        int* num_ptr = va_arg(*args, int*);
        int base = va_arg(*args, int);
        
        if (is_sscanf) {
            long long result = str_to_int_base_ptr(str, base, 1);
            *num_ptr = (int)result;
        } else {
            char buffer[100] = {0};
            int i = 0;
            int c;
            
            while (i < 99) {
                c = fgetc(stream);
                if (c == EOF || isspace(c)) {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                buffer[i++] = c;
            }
            buffer[i] = '\0';
            
            const char* temp = buffer;
            long long result = str_to_int_base_ptr(&temp, base, 1);
            *num_ptr = (int)result;
        }
        
        *format = fmt + 2;
        return 1;
    }
    
    char specifier[3] = { '%', *fmt, '\0' };
    *format = fmt + 1;
    
    if (is_sscanf) {
        return vsscanf(*str, specifier, *args);
    } else {
        return vfscanf(stream, specifier, *args);
    }
}

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int total_matches = 0;
    const char* ptr = format;
    
    while (*ptr) {
        if (*ptr == '%') {
            int matches = process_input_specifier(stream, NULL, &ptr, &args, 0);
            if (matches <= 0) break;
            total_matches += matches;
        } else {
            int c = fgetc(stream);
            if (c == EOF || c != *ptr) {
                if (c != EOF) ungetc(c, stream);
                break;
            }
            ptr++;
        }
    }
    
    va_end(args);
    return total_matches;
}

int oversscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int total_matches = 0;
    const char* fmt_ptr = format;
    const char* str_ptr = str;
    
    while (*fmt_ptr && *str_ptr) {
        if (*fmt_ptr == '%') {
            int matches = process_input_specifier(NULL, &str_ptr, &fmt_ptr, &args, 1);
            if (matches <= 0) break;
            total_matches += matches;
        } else {
            if (*fmt_ptr != *str_ptr) break;
            fmt_ptr++;
            str_ptr++;
        }
    }
    
    va_end(args);
    return total_matches;
}