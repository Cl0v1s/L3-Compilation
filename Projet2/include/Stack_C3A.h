#ifndef STACK_C3A_H
#define STACK_C3A_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Stack_C3A
{
    int* values;
    int* adr;
    int* size;
    int refsLength;
    int valuesLength;
};

struct Stack_C3A* Stack_C3A_init();

int Stack_C3A_push(struct Stack_C3A* _stack, int size);

void Stack_C3A_setValue(struct Stack_C3A* _stack, int index, int value);

int Stack_C3A_getValue(struct Stack_C3A* _stack, int index);



#endif //STACK_C3A_H
