#include "Variable.h"

struct Type* Type_INT = 0;
struct Type* Type_BOOL = 0;
struct Type* Type_VOID = 0;

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
    if(type1->type == VOID)
        return true;
    if( (type1->type == INT && type2->type == BOOL) ||  (type1->type == BOOL && type2->type == INT))
        return true;
    if(type1->type != type2->type)
        return false;
    if(type1->type == ARRAY)
        return Type_check(type1->child, type2->child);
    return true;
}

struct Type* Type_getBaseType(struct Type* type)
{
    if(type->type == ARRAY)
        return Type_getBaseType(type->child);
    return type;
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

    if(var->type->type == BOOL && value != false)
        value = true;
    var->value = malloc(sizeof(int));

    *((int*)var->value) = value;
#ifdef DEBUG
    //printf("Variable_set := %d\n", value);
#endif
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
#ifdef DEBUG
    //printf("Variable_get := %d\n", *((int*)var->value));
#endif
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
        printf("Cant call that on non-array.\n");
        exit(-1);
    }

    struct Variable* var = malloc(sizeof(struct Variable));
    var->type = type;
    var->size = length;
    var->value = malloc(sizeof(int));
    *(int*)var->value = Stack_push(stack, length);
    // Initialisation des valeurs du nouveau tableau
    for(int i = 0; i < var->size; i++)
    {
        Variable_arraySet(var, stack, Variable_init(type->child), i);
    }
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
    if(index < 0 || index >= array->size)
    {
        printf("Index out of range.\n");
        exit(-1);
    }
    if(array->value == 0)
    {
        printf("Array must be initialized.\n");
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
    if(index < 0 || index >= array->size)
    {
        printf("Index out of range.\n");
        exit(-1);
    }
    if(array->value == 0)
    {
        printf("Array must be initialized.\n");
        exit(-1);
    }

    struct Variable* res = Stack_getVariable(stack, *(int*)array->value+index);

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
    // TODO: appeler stack remove ici, grosse fuite en vue
    //Stack_remove(stack, *(int*)dest->value, dest->size);
    dest->type = Type_copy(src->type);
    if(dest->value != 0)
        free(dest->value);
    dest->value = malloc(sizeof(int));
    (*(int*)dest->value) = Stack_push(stack, src->size);
    dest->size = src->size;
    int src_index = (*(int*)src->value);
    int dest_index = (*(int*)dest->value);
    for(int i = 0; i!= dest->size; i++)
    {
        Stack_setVariable(stack, Stack_getVariable(stack, src_index+i), dest_index+i);
    }
}
