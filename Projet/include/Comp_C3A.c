#include "Comp_C3A.h"


Env* Comp_C3A_declareVariables(struct QuadList* list)
{
    Env* env = malloc(sizeof(Env));
    Env_init(env);

    struct Quad* current = list->start;
    int offset = 0;
    do
    {
        if( current == 0)
            break;
        if(current->operation == Afc || current->operation == Af)
        {
            // On ne teste pas la pré-existence, si la variable change de position c'est pas grave
            Env_set_value(env, current->destination, offset);
            offset = offset + 1;
        }
        current = current->next;
    }
    while(list->start != list->end && current != 0);

    return env;
}

void C3A_Compile_Y86(struct QuadList* list)
{
    Env* variablesOffset = Comp_C3A_declareVariables(list);
    struct Quad* current = list->start;
    do
    {
        if( current == 0)
            break;
        Comp_C3A_translate(current,0x400,variablesOffset);
        current = current->next;
    }
    while(list->start != list->end && current != 0);
}

void Comp_C3A_translate(struct Quad* quad, int memorystart, Env* variablesOffset)
{
    int tmp;
    switch(quad->operation)
    {
        case Afc:
            tmp = Value_get(quad->arg1, 0); // on peut passer env nul, c'est une valeur numéraire
            printf("irmovl $%d, %%eax\n", tmp);
            tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
            printf("rmmovl %%eax, %#04x\n", tmp);
        break;
        case Af:
            if(quad->arg2->type == 'I')
            {
                tmp = Value_get(quad->arg2, 0); // on peut passer env nul, c'est une valeur numéraire
                printf("irmovl $%d, %%eax\n", tmp);
                tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
                printf("rmmovl %%eax, %#04x\n", tmp);
            }
            else if(quad->arg2->type == 'V')
            {
                printf()
            }
        break;
    }
}