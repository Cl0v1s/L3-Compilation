//
// Created by clovis on 08/04/17.
//

#include "Variable.h"

struct Collector collector;

struct Type* Type_INT = 0;
struct Type* Type_BOOL = 0;
struct Type* Type_VOID = 0;

void TypeSystem_init()
{
    Type_BOOL = Type_init(BOOL, 0);
    Type_INT = Type_init(INT, 0);
    Type_VOID = Type_init(VOID, 0);
}

void Collector_init()
{
    collector.list = malloc(0);
    collector.length = 0;
}

void Collector_register(struct Variable* var)
{
    struct Variable** list = malloc((collector.length+1)*sizeof(struct Variable*));
    memcpy(list, collector.list, collector.length*sizeof(struct Variable*));
    list[collector.length] = var;
    free(collector.list);
    collector.list = list;
    collector.length++;
}

void Collector_clean()
{
    int rm = 0;
    for(int i = 0; i < collector.length; i++)
    {
        if(collector.list[i]->refs == 0)
            rm++;
    }
    if(rm <= 0)
        return;
    struct Variable** list = malloc((collector.length-rm)*sizeof(struct Variable*));
    int index = 0;
    for(int i = 0; i < collector.length; i++)
    {
        if(collector.list[i]->refs == 0) {
            Variable_free(collector.list[i]);
            continue;
        }
        list[index] = collector.list[i];
        index++;
    }
    free(collector.list);
    collector.list = list;
    collector.length = collector.length - rm;
}

struct Type* Type_init(int desc, struct Type* child)
{
    struct Type* type = malloc(sizeof(struct Type));
    type->desc = desc;
    type->child = child;
    return type;
}

void Type_free(struct Type* type)
{
    if(type->desc != ARRAY)
        return;
    Type_free(type->child);
    free(type);
}

struct Variable* Variable_init(struct Type* type)
{
    struct Variable* var = malloc(sizeof(struct Variable));
    var->type = type;
    var->value = 0;
    var->refs = 1;
    var->array_set = false;
    return var;
}

struct Variable* Variable_arrayInit(struct Stack* stack, struct Type* type, int size)
{
    struct Variable* var = malloc(sizeof(struct Variable));
    var->type = type;
    var->value = Stack_push(stack, size);
    var->refs = 1;
    var->array_set = true;
    return var;
}

void Variable_arraySet(struct Variable* var, int index, int value)
{

}

int Variable_arrayGet(struct Variable* var, int index);

void Variable_set(struct Variable* var, int value)
{
    var->value = value;
}

int Variable_get(struct Variable* var)
{
    return var->value;
}

void Variable_free(struct Variable* var)
{
    Type_free(var->type);
    free(var);
}