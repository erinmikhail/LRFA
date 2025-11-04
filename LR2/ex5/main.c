#include "include.h"

void check_file_lengths(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f) {
        char buffer[256];
        int line_num = 1;
        printf("Checking line lengths in %s:\n", filename);
        while (fgets(buffer, sizeof(buffer), f)) {
            int len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') len--;
            printf("Line %d: %d characters\n", line_num, len);
            line_num++;
        }
        fclose(f);
    }
}

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
        
        fclose(output_file);
        check_file_lengths(output_path);
    } else {
        printf("Ошибка открытия файлов!\n");
    }
    
    if (input_file) fclose(input_file);
    
    return 0;
}