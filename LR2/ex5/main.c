#include "include.h"

int main() {
    runAllTests();
    printf("\n");
    
    char input_path[256];
    char output_path[256];
    
    printf("Введите путь к входному файлу: ");
    fgets(input_path, sizeof(input_path), stdin);
    input_path[strcspn(input_path, "\n")] = '\0';
    
    printf("Введите путь к выходному файлу: ");
    fgets(output_path, sizeof(output_path), stdin);
    output_path[strcspn(output_path, "\n")] = '\0';
    
    FILE *input_file = fopen(input_path, "r");
    FILE *output_file = fopen(output_path, "w");
    
    if (input_file && output_file) {
        format_text(input_file, output_file);
        printf("Готово! Результат в '%s'\n", output_path);
    } else {
        printf("Ошибка открытия файлов!\n");
    }
    
    if (input_file) fclose(input_file);
    if (output_file) fclose(output_file);
    
    return 0;
}