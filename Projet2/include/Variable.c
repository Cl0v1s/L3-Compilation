#include "Variable.h"

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
    if(var->type->type == INT || var->type->type == BOOL)
    {
        var->value = malloc(sizeof(int));
        *(int*)var->value = 0;
        var->size = 0;
    }
    // Si c'est un tableau on initialize le tableau de pointeurs de structures
    if(var->type->type == ARRAY)
    {
        var->size = 0;
        var->value = malloc(var->size*sizeof(struct Variable*));
    }
    return var;
}

void Variable_arraySetType(struct Variable* var, struct Type* type)
{
	var->type = type;
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

void Variable_arraySet(struct Variable* var, int index, struct Variable* value)
{
    // Si c'est tableau
    if(var->type->type != ARRAY)
    {
        printf("Cant call Variable_arraySet on INT/BOOL.\n");
        exit(-1);
    }
   	//Si le type des elements est réglé, on vérifie le type de la valeur à insérer
    if(Type_check(var->type->child, value->type) == false)
    {
        printf("Cant insert, wrong var type\n");
        exit(-1);
    }


    //Si l'index est supérieur à la taille déjà allouée, on réalloue
    if(index < var->size)
    {
        ((struct Variable**)var->value)[index] = value;
    }
    else
    {
        struct Variable** tab;
        tab = malloc((index+1)*sizeof(struct Variable*));
        memcpy(tab, var->value, var->size*sizeof(struct Variable*));
        free(var->value);
        var->size = index+1;
        tab[index] = value;
        var->value = tab;

    }
}

struct Variable* Variable_arrayGet(struct Variable* tab, struct Stack* sta, int index)
{
    if(tab->type->type != ARRAY)
    {
        printf("Cant call Variable_arrayGet on INT/BOOL.\n");
        exit(-1);
    }
    if(index >= tab->size)
    {
        printf("Index out of range.\n");
        exit(-1);
    }
    return ((struct Variable*)sta[tab->value + index];
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

void Variable_free(struct Variable* var)
{
    if(var->size > 0)
    {
        struct Variable* value = (struct Variable*)var->value;
        for(int i = 0; i != var->size; i++)
        {
            Variable_free(value);
            value++;
        }

    }
    else
        free(var->value);
    free(var);
}

/*int main()
{
    struct Variable* var = Variable_init(INT);
    int a = 10;
    Variable_set(var, &a);
    Variable_print(var);

    struct Variable* var2 = Variable_init(INT);
    a = 100;
    Variable_set(var2, &a);
    Variable_print(var2);

    int size = ARRAY(1);
    struct Variable* var1 = Variable_init(size);
    Variable_arraySet(var1, 0, var);
    Variable_arraySet(var1, 1, var2);
    Variable_arraySet(var1, 1, var2);
    Variable_print(var1);

    size = ARRAY(1);
    printf("size: %d\n", size);
    struct Variable* array = Variable_init(size);
    Variable_arraySet(array, 0, var);
    Variable_arraySet(array, 1, var1);

    Variable_print(array);



}*/
