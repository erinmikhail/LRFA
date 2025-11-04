#include "include.h"

bool is_printAble(char c){
    return c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '\0';
}

void add_space(char *line, int current_len) {
    const int target_len = 80;
    
    if (current_len >= target_len) {
        return;
    }

    int word_count = 0;
    int words_start[256] = {0};
    int words_end[256] = {0};
    
    int in_word = 0;
    for (int i = 0; i < current_len; i++) {
        if (is_printAble(line[i])) {
            if (!in_word) {
                words_start[word_count] = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                words_end[word_count] = i;
                word_count++;
                in_word = 0;
            }
        }
    }
    if (in_word) {
        words_end[word_count] = current_len;
        word_count++;
    }

    if (word_count <= 1) {
        return;
    }

    int space_count = word_count - 1;
    int total_spaces_to_add = target_len - current_len;
    int spaces_per_gap = total_spaces_to_add / space_count;
    int extra_spaces = total_spaces_to_add % space_count;

    char new_line[512] = {0};
    int new_index = 0;

    for (int i = 0; i < word_count; i++) {
        int word_len = words_end[i] - words_start[i];
        for (int j = 0; j < word_len; j++) {
            new_line[new_index++] = line[words_start[i] + j];
        }
        
        if (i < word_count - 1) {
            new_line[new_index++] = ' ';
            for (int j = 0; j < spaces_per_gap; j++) {
                new_line[new_index++] = ' ';
            }
            if (extra_spaces > 0) {
                new_line[new_index++] = ' ';
                extra_spaces--;
            }
        }
    }

    strcpy(line, new_line);
}

void process_line(const char *input_line, FILE *output) {
    char line[1024];
    strcpy(line, input_line);
    
    int len = strlen(line);
    if (len > 0 && line[len-1] == '\n') {
        line[len-1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(output, "\n");
        return;
    }

    if (len <= 80) {
        fprintf(output, "%s\n", line);
        return;
    }

    int start = 0;
    
    while (start < len) {
        if (len - start <= 80) {
            fprintf(output, "%s\n", line + start);
            break;
        }

        int end = start + 80;
        int break_pos = end;
        
        while (break_pos > start && line[break_pos] != ' ') {
            break_pos--;
        }

        if (break_pos == start) {
            break_pos = end;
        }

        char segment[256] = {0};
        strncpy(segment, line + start, break_pos - start);
        segment[break_pos - start] = '\0';

        int segment_len = strlen(segment);
        if (segment_len < 80) {
            add_space(segment, segment_len);
        }
        
        fprintf(output, "%s\n", segment);

        start = break_pos;
        while (start < len && line[start] == ' ') {
            start++;
        }
    }
}

void format_text(FILE *input, FILE *output) {
    char line[1024];

    while (fgets(line, sizeof(line), input) != NULL) {
        process_line(line, output);
    }
}