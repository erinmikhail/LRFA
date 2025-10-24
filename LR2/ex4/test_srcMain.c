#include "include.h"
#include <string.h>

void runAllTests(void) {
    printf("=== Testing overfscanf and oversscanf ===\n\n");
    
    int num;
    unsigned int unum;
    float fnum;
    char str_buf[100];
    char ch;
    
    printf("1. Testing standard specifiers with oversscanf:\n");
    const char* std_input = "42 3.14 hello A";
    oversscanf(std_input, "%d %f %s %c", &num, &fnum, str_buf, &ch);
    printf("Standard: int=%d float=%.2f string='%s' char='%c'\n", num, fnum, str_buf, ch);
    
    printf("\n2. Testing %%Ro (Roman numerals input):\n");
    const char* roman_input = "XIV 2023";
    oversscanf(roman_input, "%Ro", &num);
    printf("Roman 'XIV' = %d\n", num);
    
    printf("\n3. Testing %%Zr (Zeckendorf input):\n");
    const char* zeck_input = "1001011 123";
    oversscanf(zeck_input, "%Zr", &unum);
    printf("Zeckendorf '1001011' = %u\n", unum);
    
    printf("\n4. Testing %%Cv (Custom base lowercase input):\n");
    const char* base_input = "ff 255";
    oversscanf(base_input, "%Cv", &num, 16);
    printf("Hex 'ff' = %d\n", num);
    
    printf("\n5. Testing %%CV (Custom base uppercase input):\n");
    const char* base_input_upper = "FF 255";
    oversscanf(base_input_upper, "%CV", &num, 16);
    printf("Hex 'FF' = %d\n", num);
    
    printf("\n6. Testing mixed formats:\n");
    const char* mixed_input = "XII 101011 1a 1A 99 7.5";
    int r1, r2, r3;
    unsigned int z;
    float f;
    oversscanf(mixed_input, "%Ro %Zr %Cv %CV %d %f", &r1, &z, &r2, 16, &r3, 16, &num, &f);
    printf("Mixed: Roman=%d, Zeck=%u, Hex(lower)=%d, Hex(upper)=%d, Int=%d, Float=%.1f\n", 
           r1, z, r2, r3, num, f);
    
    printf("\n7. Testing file input with overfscanf:\n");
    FILE* test_file = fopen("test_input.txt", "w+");
    if (test_file) {
        fprintf(test_file, "XXV 10011 fe FE 123 8.75");
        rewind(test_file);
        
        int file_roman, file_hex1, file_hex2, file_int;
        unsigned int file_zeck;
        float file_float;
        overfscanf(test_file, "%Ro %Zr %Cv %CV %d %f", 
                  &file_roman, &file_zeck, &file_hex1, 16, &file_hex2, 16, &file_int, &file_float);
        printf("File input: Roman=%d, Zeck=%u, Hex1=%d, Hex2=%d, Int=%d, Float=%.2f\n", 
               file_roman, file_zeck, file_hex1, file_hex2, file_int, file_float);
        fclose(test_file);
        remove("test_input.txt");
    }
    
    printf("\n8. Testing width and other standard modifiers:\n");
    const char* width_input = "12345 hello";
    char narrow_str[10];
    oversscanf(width_input, "%5d %5s", &num, narrow_str);
    printf("Width modifiers: num=%d, str='%s'\n", num, narrow_str);
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
}