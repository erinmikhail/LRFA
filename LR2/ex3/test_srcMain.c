#include "include.h"
#include <string.h>
#include <assert.h>

void runAllTests(void) {
    printf("=== Testing overfprintf and oversprintf ===\n\n");
    
    char buffer[1000];
    
    // Test %Ro - Roman numerals
    printf("1. Testing %%Ro (Roman numerals):\n");
    overfprintf(stdout, "15 in Roman: %Ro\n", 15);
    overfprintf(stdout, "2023 in Roman: %Ro\n", 2023);
    oversprintf(buffer, "3999 in Roman: %Ro", 3999);
    printf("%s\n", buffer);
    printf("\n");
    
    // Test %Zr - Zeckendorf representation
    printf("2. Testing %%Zr (Zeckendorf):\n");
    overfprintf(stdout, "20 in Zeckendorf: %Zr\n", 20);
    overfprintf(stdout, "100 in Zeckendorf: %Zr\n", 100);
    oversprintf(buffer, "1 in Zeckendorf: %Zr", 1);
    printf("%s\n", buffer);
    printf("\n");
    
    // Test %Cv - Custom base lowercase
    printf("3. Testing %%Cv (Custom base lowercase):\n");
    overfprintf(stdout, "255 in base 16: %Cv\n", 255, 16);
    overfprintf(stdout, "42 in base 2: %Cv\n", 42, 2);
    oversprintf(buffer, "-100 in base 8: %Cv", -100, 8);
    printf("%s\n", buffer);
    printf("\n");
    
    // Test %CV - Custom base uppercase
    printf("4. Testing %%CV (Custom base uppercase):\n");
    overfprintf(stdout, "255 in base 16: %CV\n", 255, 16);
    overfprintf(stdout, "42 in base 2: %CV\n", 42, 2);
    printf("\n");
    
    // Test %to - String to int lowercase
    printf("5. Testing %%to (String to int lowercase):\n");
    overfprintf(stdout, "\"ff\" from base 16: %to\n", "ff", 16);
    overfprintf(stdout, "\"1010\" from base 2: %to\n", "1010", 2);
    printf("\n");
    
    // Test %TO - String to int uppercase
    printf("6. Testing %%TO (String to int uppercase):\n");
    overfprintf(stdout, "\"FF\" from base 16: %TO\n", "FF", 16);
    overfprintf(stdout, "\"1A\" from base 16: %TO\n", "1A", 16);
    printf("\n");
    
    // Test %mi - Memory dump int
    printf("7. Testing %%mi (Memory dump int):\n");
    overfprintf(stdout, "Memory dump of 255: %mi\n", 255);
    overfprintf(stdout, "Memory dump of -1: %mi\n", -1);
    printf("\n");
    
    // Test %mu - Memory dump unsigned int
    printf("8. Testing %%mu (Memory dump unsigned int):\n");
    overfprintf(stdout, "Memory dump of 255: %mu\n", 255u);
    overfprintf(stdout, "Memory dump of 1000: %mu\n", 1000u);
    printf("\n");
    
    // Test %md - Memory dump double
    printf("9. Testing %%md (Memory dump double):\n");
    overfprintf(stdout, "Memory dump of 3.14: %md\n", 3.14);
    overfprintf(stdout, "Memory dump of -2.5: %md\n", -2.5);
    printf("\n");
    
    // Test %mf - Memory dump float
    printf("10. Testing %%mf (Memory dump float):\n");
    overfprintf(stdout, "Memory dump of 1.5f: %mf\n", 1.5f);
    overfprintf(stdout, "Memory dump of -0.5f: %mf\n", -0.5f);
    printf("\n");
    
    // Mixed test
    printf("11. Mixed format test:\n");
    oversprintf(buffer, "Roman: %Ro, Zeckendorf: %Zr, Hex: %Cv", 42, 42, 42, 16);
    printf("%s\n", buffer);
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
}