#include <stdio.h>
#include "../include/logger.h"

static FILE* log_file = NULL;

void init_logger(const char* filename){
    if (log_file != NULL){
        fclose(log_file);
    }
    log_file = fopen(filename, "w");
}

void log_operation(int line_num, const char* command, const char* variables, const char* operation){
    if (log_file != NULL){
        fprintf(log_file, "[%d] %s | %s | %s\n", line_num, command, variables, operation);
    }
}

void close_logger(){
    if (log_file != NULL){
        fclose(log_file);
        log_file = NULL;
    }
}