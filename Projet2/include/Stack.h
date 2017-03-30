#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

struct Stack
{
    struct Variable** vars;
    int size;
};

struct Stack* Stack_init();

void Stack_push();

#endif
