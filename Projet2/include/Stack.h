#ifndef STACK_H
#define STACK_H

struct Stack
{
    struct Variable* values;
    int length;
}

struct Stack* Stack_init();

void Stack_push();

#endif