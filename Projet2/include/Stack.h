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

void Stack_remove(struct Stack* _stack, int index, int size);


void Stack_removeArray(struct Stack* _stack, struct Variable* start);

/**
 * Stack_trunk : tronque le Stack passé le tableau pointé par last
 * @param _stack : le tas
 * @param last : variable pointant sur le dernier tableau de valeurs à garder
 */
void Stack_trunk(struct Stack* _stack, struct Variable* last);

/**
 * Stack_safeDeleteRange : supprime dans le tas les variables entre un tableau et un autre
 * @param _stack
 * @param start
 * @param end
 */
void Stack_safeDeleteRange(struct Stack* _stack, struct Variable* start, struct Variable* end);

struct Variable* Stack_getVariable(struct Stack* _stack, int index);

void Stack_setVariable(struct Stack* _stack, struct Variable* var, int index);

#endif
