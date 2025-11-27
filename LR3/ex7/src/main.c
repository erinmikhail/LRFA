#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/logger.h"

#define MAX_LINE_LENGTH 256

void process_file(const char* input_filename){
    FILE* file = fopen(input_filename, "r");
    if (!file){
        printf("error: cannot open file\n");
        return;
    }

    init_interpreter();
    init_logger("trace.log");
    char line[MAX_LINE_LENGTH];
    int line_num = 1;
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0){
            line_num++;
            continue;
        }

        char operation_desc[50];
        execute_line(line, operation_desc);

        char variables_str[512];
        get_variables_state(variables_str, sizeof(variables_str));

        log_operation(line_num, line, variables_str, operation_desc);
        line_num++;
    }

    fclose(file);
    close_logger();
    cleanup_interpreter();
}

int main(int argc, char* argv[]){
    const char* input_filename = "input.txt";

    if (argc > 1){
        input_filename = argv[1];
    }

    process_file(input_filename);
    printf("processing complete.\n");
    return 0;
}