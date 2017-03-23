#include "Variable.h"

struct Variable* Variable_init(int type)
{
    if( type < 0 )
    {
        printf("Invalid type or size.\n");
        exit(-1);
    }

    struct Variable* var = malloc(sizeof(struct Variable));
    var->size = type;
    if(var->size == 0)
    {
        var->value = malloc(sizeof(int));
        *(int*)var->value = 0;
    }
    // Si c'est un tableau on initialize le tableau de pointeurs de structures
    if(var->size > 0)
    {
        var->value = malloc(var->size*sizeof(struct Variable**));
        for(int i = 0; i != var->size; i++)
        {
            ((struct Variable**)var->value)[i] = 0;
        }
    }
    return var;
}

void Variable_set(struct Variable* var,int* value)
{
    // Si c'est un int ou un booléen
    if(var->size != 0)
    {
        printf("Cant call Variable_set on array.\n");
        exit(-1);
    }
    if(var->value != 0)
        free(var->value);
    var->value = malloc(sizeof(int));
    *((int*)var->value) = *value; 
}

int Variable_get(struct Variable* var)
{
    //printf("Getting %p -> %p:\n", var, var->value);
    // Si c'est un int ou un booléen
    if(var->size != 0)
    {
        printf("Cant call Variable_get on array.\n");
        exit(-1);
    }
    return *((int*)var->value); 
}

void Variable_arraySet(struct Variable* var, int index, struct Variable* value)
{
    // Si c'est tableau
    if(var->size <= 0)
    {
        printf("Cant call Variable_arraySet on INT/BOOL.\n");
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
        tab = malloc((index+1)*sizeof(struct Variable**));
        memcpy(tab, var->value, var->size*sizeof(struct Variable**));
        free(var->value);
        var->size = index+1;
        tab[index] = value;
        var->value = tab;
        
    }
}

struct Variable* Variable_arrayGet(struct Variable* var, int index)
{
    if(var->size <= 0)
    {
        printf("Cant call Variable_arrayGet on INT/BOOL.\n");
        exit(-1);  
    }
    if(index >= var->size)
    {
        printf("Index out of range.\n");
        exit(-1); 
    }
    return ((struct Variable**)var->value)[index];
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

int main()
{
    struct Variable* var = Variable_init(INT);
    int a = 10;
    Variable_set(var, &a);
    Variable_print(var);

    struct Variable* var1 = Variable_init(BOOL);
    a = 100;
    Variable_set(var1, &a);
    Variable_print(var1);

    int size = ARRAY(1);
    printf("size: %d\n", size);
    struct Variable* array = Variable_init(size);
    Variable_arraySet(array, 0, var);
    Variable_arraySet(array, 1, var1);

    Variable_print(array);
}