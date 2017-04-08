//
// Created by clovis on 08/04/17.
//

#ifndef L3_COMPILATION_VARIABLE_H
#define L3_COMPILATION_VARIABLE_H

#include <stdlib.h>
#include <string.h>

#include "Stack.h"

#define BOOL 0
#define INT 1
#define ARRAY 2
#define VOID 3

#define true 1
#define false 0

extern struct Type* Type_INT;
extern struct Type* Type_BOOL;
extern struct Type* Type_VOID;

struct Type
{
    int desc;
    struct Type* child;
};

struct Variable
{
    struct Type* type;
    int value;
    int refs;
    int array_set;
};


struct Collector
{
    struct Variable** list;
    int length;
};

void TypeSystem_init();

void Collector_init();

void Collector_register(struct Variable* var);

void Collector_clean();

struct Type* Type_init(int desc, struct Type* child);
void Type_free(struct Type* type);

struct Variable* Variable_init(struct Type*);

struct Variable* Variable_arrayInit(struct Stack* stack, struct Type*, int size);

void Variable_arraySet(struct Variable* var, int index, int value);

int Variable_arrayGet(struct Variable* var, int index);

void Variable_set(struct Variable* var, int value);

int Variable_get(struct Variable* var);

void Variable_free(struct Variable* var);

#endif //L3_COMPILATION_VARIABLE_H
