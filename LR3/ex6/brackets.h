#ifndef BRACKERS_H
#define BRACKETS_H

#define STACK_SIZE 1000

typedef struct {
    char data[STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack *stack);
int is_empty(Stack *stack);
void push(Stack *stack, char c);
char pop(Stack *stack);

int is_open_bracket(char c);
int is_close_bracket(char c);
int is_matching_pair(char open, char close);

int check_brackets(const char *str);

#endif