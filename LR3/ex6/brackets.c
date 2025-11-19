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

