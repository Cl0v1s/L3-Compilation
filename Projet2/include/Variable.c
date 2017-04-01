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
    // Si c'est un tableau on initialize le tableau de pointeurs de structures
    // Ca va va pas, Va voir Variable_arrayInit
    /*if(var->type->type == ARRAY)
    {
        var->size = 0;
        var->value = malloc(var->size*sizeof(struct Variable*));
    }*/
    return var;
}

struct Variable* Variable_arrayInit(struct Type* type, struct Stack* stack, int length)
{
    // TU devrais comprendre avec cette signature
    return 0;
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


    //Si l'index est inférieur à la taille déjà allouée, on réalloue
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

// TODO : La version que je pense, après à toi de voir ?
void Variable_arraySet2(struct Variable* array, struct Variable* value, struct Stack* stack, int index){
    // S'il s'agit d'un tableau
    if(array->type->type != ARRAY){
        printf("Can't call Variable_arraySet on INT/BOOL.\n");
    }

    // Si l'on veut set un élément de type correct
    if(Type_check(array->type->child, value->type) == false){
        printf("Can't set, wrong var type.\n");
        exit(-1);
    }
    else {
        // L'allocation doit être effectuée au moment du push, pas d'allocation dynamique dans le tas pour un tableau spécifique, trop compliqué
        Stack_setVariable(stack, value, *(int*)array->value + index);
    }
}

// TODO : On aura besoin de push un tableau vide de values dans le stack du coup
void Variable_arrayInit(struct Variable* array, struct Variable* values, struct Stack* stack){
    // Si c'est un tableau
    if(array->type->type != ARRAY){
        printf("Can't call Variable_arraySet on INT/BOOL.\n");
        exit(-1);
    }
    //Si le type des elements est réglé, on vérifie le type de la valeur à insérer
    if(Type_check(array->type->child, values->type) == false)
    {
        printf("Cant insert, wrong var type\n");
        exit(-1);
    }
    // Setting array first index in stack and pushing values to stack
    array->value = (void*)Stack_push(stack, values);
}

// TODO : J'ai modifie un peu la fonction get du coup
struct Variable* Variable_arrayGet(struct Variable* tab, struct Stack* stack, int index)
{
    // S'il s'agit d'un tableau
    if(tab->type->type != ARRAY)
    {
        printf("Cant call Variable_arrayGet on INT/BOOL.\n");
        exit(-1);
    }
    // Si l'index est correct
    if(index >= tab->size)
    {
        printf("Index out of range.\n");
        exit(-1);
    }
    // Tab->value est l'index de début de tableau dans le stack, index est le décalage
    return Stack_getVariable(stack, *(int*)tab->value + index);
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
