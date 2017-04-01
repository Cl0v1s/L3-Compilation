#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Stack
{
    struct Variable** vars;
    int size;
};

struct Stack* Stack_init();

int Stack_push(struct Stack* _stack, int size);

void Stack_remove(struct Stack* _stack, int start, int size);

struct Variable* Stack_getVariable(struct Stack* _stack, int index);

void Stack_setVariable(struct Stack* _stack, struct Variable* var, int index);

#endif
