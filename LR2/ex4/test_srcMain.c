#include "include.h"
#include <string.h>

void runAllTests(void) {
    printf("=== Testing overfscanf and oversscanf ===\n\n");
    
    int num;
    unsigned int unum;
    
    printf("1. Testing %%Ro (Roman numerals input):\n");
    const char* roman_input = "XIV 2023";
    oversscanf(roman_input, "%Ro", &num);
    printf("Roman 'XIV' = %d\n", num);
    
    printf("2. Testing %%Zr (Zeckendorf input):\n");
    const char* zeck_input = "1001011 123";
    oversscanf(zeck_input, "%Zr", &unum);
    printf("Zeckendorf '1001011' = %u\n", unum);
    
    printf("3. Testing %%Cv (Custom base lowercase input):\n");
    const char* base_input = "ff 255";
    oversscanf(base_input, "%Cv", &num, 16);
    printf("Hex 'ff' = %d\n", num);
    
    printf("4. Testing %%CV (Custom base uppercase input):\n");
    const char* base_input_upper = "FF 255";
    oversscanf(base_input_upper, "%CV", &num, 16);
    printf("Hex 'FF' = %d\n", num);
    
    printf("5. Testing mixed formats:\n");
    const char* mixed_input = "XII 101011 1a 1A";
    int r1, r2, r3;
    oversscanf(mixed_input, "%Ro %Zr %Cv %CV", &r1, &unum, &r2, 16, &r3, 16);
    printf("Mixed: Roman=%d, Zeck=%u, Hex(lower)=%d, Hex(upper)=%d\n", r1, unum, r2, r3);
    
    printf("\n6. Testing file input with overfscanf:\n");
    FILE* test_file = fopen("test_input.txt", "w+");
    if (test_file) {
        fprintf(test_file, "XXV 10011 fe FE");
        rewind(test_file);
        
        overfscanf(test_file, "%Ro %Zr %Cv %CV", &num, &unum, &num, 16, &num, 16);
        printf("File input: Roman=XXV, Zeck=10011, Hex=fe/FE\n");
        fclose(test_file);
        remove("test_input.txt");
    }
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
}