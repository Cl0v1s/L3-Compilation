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

int TypeSystem_isInit()
{
    if(Type_BOOL == 0 || Type_INT == 0 || Type_VOID == 0)
        return false;
    return true;
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

void Collector_clean(struct Stack* stack)
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
            Variable_free(collector.list[i], stack);
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

int Type_check(struct Type* type1, struct Type* type2)
{

    if(type1->desc == VOID || type2->desc == VOID)
        return true;
    if( (type1->desc == BOOL && type2->desc == INT) || (type1->desc == INT && type2->desc == BOOL))
        return true;
    if(type1->desc != type2->desc)
        return false;
    if(type1->desc == ARRAY)
        return Type_check(type1->child, type2->child);
    return true;
}

int Type_check_strict(struct Type* type1, struct Type* type2)
{
    if(type1->desc != type2->desc)
        return false;
    if(type1->desc == ARRAY)
        return Type_check(type1->child, type2->child);
    return true;
}

void Type_free(struct Type* type)
{
    if(type->desc != ARRAY)
        return;
    Type_free(type->child);
    free(type);
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

struct Variable* Variable_arrayRef(struct Type* type, int value)
{
    struct Variable* var = malloc(sizeof(struct Variable));
    var->type = type;
    var->value = value;
    var->refs = 1;
    var->array_set = true;
    return var;
}

void Variable_arrayCopy(struct Stack* stack, struct Variable* var1, struct Variable* var2)
{
    if(Type_check(var1->type, var2->type) == false)
    {
        printf("VARIABLE: cant copy two arrays from different types.\n");
        exit(-1);
    }
    if(var2->array_set == false)
    {
        printf("VARIABLE: cant copy a non initialized array.\n");
        exit(-1);
    }
    if(var1->array_set == true)
        Stack_remove(stack, var1->value);
    var1->value = Stack_push(stack, stack->size[var2->value]);
    for(int i = 0; i < stack->size[var2->value]; i++)
    {
        Variable_arraySet(var1, stack, i, Variable_arrayGet(var2, stack, i));
    }
}

void Variable_arraySet(struct Variable* var, struct Stack* stack, int index, int value)
{
    if(index > stack->size[var->value])
    {
        printf("VARIABLE: Index out of range.\n");
        exit(-1);
    }
    index = index + stack->adr[var->value];
    Stack_setValue(stack, index, value);
}

int Variable_arrayGet(struct Variable* var, struct Stack* stack, int index)
{
    if(index > stack->size[var->value])
    {
        printf("VARIABLE: Index out of range.\n");
        exit(-1);
    }
    index = index + stack->adr[var->value];
    return Stack_getValue(stack, index);
}

void Variable_free(struct Variable* var, struct Stack* stack)
{
    if(var->array_set == true)
        Stack_remove(stack, var->value);
    Type_free(var->type);
    free(var);
}

void Variable_print(struct Variable* var, struct Stack* stack)
{
    printf("Variable: type: %d index: %d adr: %d size: %d\n", var->type->desc, var->value, stack->adr[var->value], stack->size[var->value]);
}