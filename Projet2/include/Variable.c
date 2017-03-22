#include "Variable.h"

struct Variable* Variable_init(int type)
{
    if((type != INT && type != BOOL) || type < 0 )
    {
        printf("Invalid type or size.\n");
        exit(-1);
    }

    struct Variable* var = malloc(sizeof(struct Variable));
    var->size = type;
    var->value = 0;
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
    var->value = malloc(sizeof(int));
    *var->value = *value;
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