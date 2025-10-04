#include <stdio.h>
#include <string.h>



int is_latin_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_arabic_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_space(char c) {
    return c == ' ';
}

void process_d(FILE *in, FILE *out) {
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (!is_arabic_digit(c))
            fputc(c, out);
    }
}

void process_i(FILE *in, FILE *out) {
    char line[1024];
    while (fgets(line, sizeof(line), in)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (is_latin_letter(line[i]))
                count++;
        }
        fprintf(out, "%d\n", count);
    }
}

void process_s(FILE *in, FILE *out) {
    char line[1024];
    while (fgets(line, sizeof(line), in)) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            char ch = line[i];
            if (!is_latin_letter(ch) && !is_arabic_digit(ch) && !is_space(ch))
                count++;
        }
        fprintf(out, "%d\n", count);
    }
}

void process_a(FILE *in, FILE *out) {
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (is_arabic_digit(c))
            fputc(c, out);
        else
            fprintf(out, "%02X", (unsigned char)c);
    }
}

void get_filename(const char *path, char *filename) {
    int len = strlen(path);
    int last_slash = -1;
    
    for (int i = 0; i < len; i++) {
        if (path[i] == '/' || path[i] == '\\') {
            last_slash = i;
        }
    }

    if (last_slash == -1) {
        strcpy(filename, path);
    } else {
        strcpy(filename, path + last_slash + 1);
    }
}


int main(int argc, char *argv[]){

    if (argc < 3){
        printf("не достаточно данных");
        return 1;
    }

    char *flag = argv[1];
    char *input_path = argv[2];
    char output_path[256];

    if (flag[0] != '-' && flag[0] != '/'){
        printf("неверный флаг");
        return 1;
    }

    char action_flag;
    int has_n = 0;

    if (flag[1] == 'n' && flag[2] != '\0'){
        has_n = 1;
        action_flag = flag[2];
    } else {
        action_flag = flag[1];
    }

    if (has_n && argc >= 4){
        strcpy(output_path, argv[3]);
    } else {
        char filename[100];
        get_filename(input_path, filename);
        sprintf(output_path, "out_%s", filename);
    }

    FILE *in = fopen(input_path, "r");
    if (!in){
        printf("файл не открывается");
        return 1;
    }

    FILE *out = fopen(output_path, "w");
    if (!out){
        printf("файл не записывается");
        fclose(in);
        return 1;
    }

    switch (action_flag) {
        case 'd': 
            process_d(in, out);
            break;
        case 'i': 
            process_i(in, out);
            break;
        case 's': 
            process_s(in, out);
            break;
        case 'a': 
            process_a(in, out);
            break;
        default:
            printf("неизвестный флаг '%c'\n", action_flag);
            fclose(in);
            fclose(out);
            return 1;
    }
    
    fclose(in);
    fclose(out);
    
    printf("выполнена успешно: %s\n", output_path);
    return 0;
}