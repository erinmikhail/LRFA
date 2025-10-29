#include "include.h"


bool is_printAble(char c){
    return c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '\0';
}

void add_space(char *line, int current_len){
    const int target_len = 80;
    int space_to_add = target_len - current_len;

    if (space_to_add <= 0){
        return;
    }

    int space_count = 0;
    for (int i = 0; i < current_len; i++){
        if(line[i] == ' '){
            space_count++;
        }
    }

    if (space_count == 0){
        return;
    }

    int base_spaces_to_add = space_to_add / space_count;
    int extra_spaces = space_to_add % space_count;
    
    char new_line[512] = {0};
    int new_index = 0;
    
    for (int i = 0; i < current_len; i++) {
        if (new_index >= 511) break;
        
        new_line[new_index++] = line[i];
        
        if (line[i] == ' ') {
            for (int j = 0; j < base_spaces_to_add; j++) {
                if (new_index >= 511) break;
                new_line[new_index++] = ' ';
            }
            if (extra_spaces > 0) {
                if (new_index >= 511) break;
                new_line[new_index++] = ' ';
                extra_spaces--;
            }
        }
    }
    
    new_line[511] = '\0';
    strcpy(line, new_line);
}

void process_line(const char *input_line, FILE *output){
    char line[1024];
    strcpy(line, input_line);

    int len = strlen(line);
    if (len > 0 && line[len-1] == '\n') {
        line[len-1] = '\0';
        len--;
    }

    if (len <= 80) {
        fprintf(output, "%s\n", line);
        return;
    }
    
    char buffer[256];
    int buffer_len = 0;
    int pos = 0;
    
    while (pos < len) {
        if (buffer_len < 80 && pos < len) {
            buffer[buffer_len++] = line[pos++];
            buffer[buffer_len] = '\0';
        } else {
            int break_pos = buffer_len;
            
            while (break_pos > 0 && buffer[break_pos] != ' ') {
                break_pos--;
            }
            
            if (break_pos == 0) {
                break_pos = buffer_len;
            }
            
            char current_line[256] = {0};
            strncpy(current_line, buffer, break_pos);
            current_line[break_pos] = '\0';
            
            int next_part_start = break_pos;
            while (next_part_start < buffer_len && buffer[next_part_start] == ' ') {
                next_part_start++;
            }
            
            int remaining_len = buffer_len - next_part_start;
            if (remaining_len > 0) {
                memmove(buffer, buffer + next_part_start, remaining_len);
            }
            buffer_len = remaining_len;
            buffer[buffer_len] = '\0';
            
            int current_len = strlen(current_line);
            if (current_len < 80) {
                add_space(current_line, current_len);
            }

            fprintf(output, "%s\n", current_line);
        }
    }
    
    if (buffer_len > 0) {
        fprintf(output, "%s\n", buffer);
    }
}

void format_text(FILE *input, FILE *output) {
    char line[1024];

    while (fgets(line, sizeof(line), input) != NULL) {
        process_line(line, output);
    }
}