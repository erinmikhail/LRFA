#include "brackets.h"
#include <stdio.h>

void init_stack(Stack *stack){
    stack->top= 0;
}

int is_empty(Stack *stack){
    return stack->top == 0;
}

void push(Stack *stack, char c){
    stack->data[stack->top] = c;
    stack->top++;
}

char pop(Stack *stack){
    stack->top--;
    return stack->data[stack->top];
}

int is_open_bracket(char c){
    return c == '(' || c == '[' || c == '{' || c == '<';
}

int is_close_bracket(char c){
    return c == ')' || c == ']' || c == '}' || c == '>';
}

int is_matching_pair(char open, char close){
    if (open == '(' && close == ')') return 1;
    if (open == '[' && close == ']') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '<' && close == '>') return 1;
    return 0;
}

