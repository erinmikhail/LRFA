#ifndef INTERPRETER_H
#define INTERPRETER_H
#define NUM_VARIABLES 26

void init_interpreter();
int execute_line(const char* line, char* operation_desc);
void get_variables_state(char* buffer, int buffer_size);
void cleanup_interpreter();

#endif