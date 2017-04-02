#include "Variable.h"


void TypeSystem_init()
{
    Type_BOOL = Type_init(BOOL, 0);
    Type_INT = Type_init(INT, 0);
    Type_VOID = Type_init(VOID, 0);

}

char TypeSystem_isInit()
{
    if(Type_BOOL == 0 || Type_INT == 0 || Type_VOID == 0)
        return false;
    return true;
}

struct Type* Type_init(int type, struct Type* child)
{
    struct Type* res = malloc(sizeof(struct Type));
    res->type = type;
    if(type == INT || type == BOOL)
    {
        res->child = 0;
    }
    else
        res->child = child;
    return res;
}

int Type_check(struct Type* type1, struct Type* type2)
{
    if(type1 == VOID)
        return true;
    if(type1->type != type2->type)
        return false;
    if(type1->type == ARRAY)
        return Type_check(type1->child, type2->child);
    return true;
}

struct VariableList* VariableList_init()
{
    struct VariableList* res = malloc(sizeof(struct VariableList));
    res->size = 0;
    res->list = malloc(0);
}

void VariableList_append(struct VariableList* vlist, struct Variable* var)
{
    int size = vlist->size + 1;
    struct Variable** newVars = malloc(size*sizeof(struct Variable*));
    memcpy(newVars, vlist->list, vlist->size*sizeof(struct Variable*));
    newVars[vlist->size] = var;
    free(vlist->list);
    vlist->list = newVars;
    vlist->size = size;
}



struct Variable* Variable_init(struct Type* type)
{
    if( type == 0 )
    {
        printf("Invalid type or size.\n");
        exit(-1);
    }

    struct Variable* var = malloc(sizeof(struct Variable));
    var->type = type;
    if(var->type->type == INT || var->type->type == BOOL || var->type->type == VOID)
    {
        var->value = malloc(sizeof(int));
        *(int*)var->value = 0;
        var->size = 0;
    }
    return var;
}



void Variable_set(struct Variable* var,int value)
{
    // Si c'est un int ou un booléen
    if(var->type->type == ARRAY)
    {
        printf("Cant call Variable_set on array.\n");
        exit(-1);
    }
    if(var->value != 0)
        free(var->value);
    var->value = malloc(sizeof(int));
    *((int*)var->value) = value;
}

int Variable_get(struct Variable* var)
{
    //printf("Getting %p -> %p:\n", var, var->value);
    // Si c'est un int ou un booléen
    if(var->type->type == ARRAY)
    {
        printf("Cant call Variable_get on array.\n");
        exit(-1);
    }
    return *((int*)var->value);
}


void Variable_print(struct Variable* var)
{
    if(var->size == 0)
    {
        printf("%d\n", Variable_get(var));
    }
    else
    {
        printf("[\n");
        struct Variable** tab = (struct Variable**)var->value;

        for(int i = 0; i!= var->size; i++)
        {
            if(tab[i] == 0)
                continue;
            Variable_print(tab[i]);
        }
        printf("]\n");
    }
}

void Type_free(struct Type* type)
{
    if(type->type != ARRAY)
    {
        return;
    }
    Type_free(type->child);
    free(type);
}

void Variable_free(struct Variable* var)
{
    if(var->type->type == ARRAY)
    {
        struct Variable* value = (struct Variable*)var->value;
        for(int i = 0; i != var->size; i++)
        {
            Variable_free(value);
            value++;
        }
        Type_free(var->type);

    }
    else
        free(var->value);
    free(var);
}

struct Variable* Variable_arrayInit(struct Type* type, struct Stack* stack, int length)
{
    if(type->type != ARRAY)
    {
        printf("Cant call that on array.\n");
        exit(-1);
    }

    struct Variable* var = malloc(sizeof(struct Variable));
    var->type = type;
    var->size = length;
    *(int*)var->value = Stack_push(stack, length);
    return var;
}


void Variable_arraySet(struct Variable* array, struct Stack* stack, struct Variable* value, int index )
{
    // Si c'est tableau
    if(array->type->type != ARRAY)
    {
        printf("Cant call Variable_arraySet on non-Array.\n");
        exit(-1);
    }
    if(index >= array->size)
    {
        printf("Index out of range.\n");
        exit(-1);
    }
    if(array->type->child->type != value->type->type)
    {
        printf("Cant insert wrong type object.\n");
        exit(-1);
    }
    Stack_setVariable(stack, value, *(int*)array->value+index);
}


struct Variable* Variable_arrayGet(struct Variable* array, struct Stack* stack, int index)
{
    // Si c'est tableau
    if(array->type->type != ARRAY)
    {
        printf("Cant call Variable_arraySet on non-Array.\n");
        exit(-1);
    }
    if(index >= array->size)
    {
        printf("Index out of range.\n");
        exit(-1);
    }
    return Stack_getVariable(stack, *(int*)array->value+index);
}

struct Type* Type_copy(struct Type* src)
{
    if(src->type == ARRAY) {
        struct Type *type = malloc(sizeof(struct Type));
        type->type = src->type;
        type->child = Type_copy(src->child);
        return type;
    }
    switch(src->type)
    {
        case VOID:
            return Type_VOID;
        case INT:
            return Type_INT;
        case BOOL:
            return Type_BOOL;
    }

}

void Variable_arrayCopy(struct Stack* stack, struct Variable* dest, struct Variable* src)
{
    Type_free(dest->type);
    Stack_remove(stack, *(int*)dest->value, dest->size);
    dest->type = Type_copy(src->type);
    (*(int*)dest->value) = Stack_push(stack, src->size);
    dest->size = src->size;
    int src_index = (*(int*)src->value);
    int dest_index = (*(int*)dest->value);
    for(int i = 0; i!= dest->size; i++)
    {
        Stack_setVariable(stack, Stack_getVariable(stack, src_index+i), dest_index+i);
    }
}
