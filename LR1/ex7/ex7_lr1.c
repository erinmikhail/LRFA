#include "ex7_lr1.h"


void print_error_message(StatusCode code) {
    switch (code) {
        case ERROR_INVALID_ARGUMENTS:
            fprintf(stderr, "Usage: program input_file output_file\n");
            break;
        case ERROR_OPEN_INPUT_FILE:
            fprintf(stderr, "Error: Cannot open input file\n");
            break;
        case ERROR_OPEN_OUTPUT_FILE:
            fprintf(stderr, "Error: Cannot open output file\n");
            break;
        case ERROR_INVALID_CHARACTER:
            fprintf(stderr, "Error: Invalid character in number\n");
            break;
        case ERROR_READING_FILE:
            fprintf(stderr, "Error: Reading from input file failed\n");
            break;
        default:
            fprintf(stderr, "Error: Unknown error occurred (code: %d)\n", code);
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_error_message(ERROR_INVALID_ARGUMENTS);
        return ERROR_INVALID_ARGUMENTS;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        print_error_message(ERROR_OPEN_INPUT_FILE);
        return ERROR_OPEN_INPUT_FILE;
    }
    
    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        print_error_message(ERROR_OPEN_OUTPUT_FILE);
        fclose(fin);
        return ERROR_OPEN_OUTPUT_FILE;
    }


    StatusCode result = process_file(fin, fout);

    fclose(fin);
    fclose(fout);
    
    if (result != SUCCESS) {
        print_error_message(result);
        return result;
    }
    
    printf("File processing completed successfully!\n");
    return SUCCESS;
}