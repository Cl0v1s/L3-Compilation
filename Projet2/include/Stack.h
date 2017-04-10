#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct Stack
{
    int* values;
    int* adr;
    int* size;
    int* refs;
    int refsLength;
    int valuesLength;
};

struct Stack* Stack_init();

struct Stack* Stack_clone(struct Stack* source);

void Stack_free(struct Stack* stack);

int Stack_push(struct Stack* _stack, int size);

void Stack_setValue(struct Stack* _stack, int index, int value);

int Stack_setValue_expand(struct Stack* _stack, int pos, int index, int value);

int Stack_getValue(struct Stack* _stack, int index);

int Stack_copy(struct Stack* stack, int index);

void Stack_ref(struct Stack* stack, int index);

void Stack_deref(struct Stack* stack, int index);

void Stack_remove(struct Stack* stack, int index);

void Stack_print(struct Stack* stack);

#endif //STACK_H