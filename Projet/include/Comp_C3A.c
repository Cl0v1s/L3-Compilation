#include "Comp_C3A.h"
int loopCounter = 0;

Env* Comp_C3A_declareVariables(struct QuadList* list, int* memoryend)
{
    Env* env = malloc(sizeof(Env));
    Env_init(env);

    struct Quad* current = list->start;
    int offset = 0;
    do
    {
        if( current == 0)
            break;
        if(current->operation == Afc || current->operation == Af || current->operation == Pl || current->operation == Mo || current->operation == Mu)
        {
            // On ne teste pas la pré-existence, si la variable change de position c'est pas grave
            Env_set_value(env, current->destination, offset);
            offset = offset + 4;
        }
        current = current->next;
    }
    while(list->start != list->end && current != 0);
    *memoryend = offset;
    return env;
}

void C3A_Compile_Y86(struct QuadList* list)
{
    int stacksize = 0x100;
    int memorystart = 0x400;
    int memoryend;
    Env* variablesOffset = Comp_C3A_declareVariables(list, &memoryend);
    memoryend = memorystart+memoryend;
    printf("irmovl %#04x, %%esp\n", memoryend+stacksize);//on règle le stack après la mémoire
    struct Quad* current = list->start;
    do
    {
        if( current == 0)
            break;
        Comp_C3A_translate(current,memorystart,variablesOffset);
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
            tmp = *(int*)quad->arg1->value; 
            printf("irmovl $%d, %%eax\n", tmp);
            tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
            printf("rmmovl %%eax, %#04x\n", tmp);
        break;
        case Af:
            if(quad->arg2->type == 'I')
            {
                tmp = *(int*)quad->arg1->value;
                printf("irmovl $%d, %%eax\n", tmp);
                tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
                printf("rmmovl %%eax, %#04x\n", tmp);
            }
            else if(quad->arg2->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg2->value);
                printf("mrmovl %#04x, %%eax\n", tmp);
                tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
                printf("rmmovl %%eax, %#04x\n", tmp);
            }
        break;
        case Pl:
            if(quad->arg1->type == 'I')
            {
                tmp = *(int*)quad->arg1->value;
                printf("irmovl $%d, %%eax\n", tmp);
            }
            else if(quad->arg1->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg1->value);
                printf("mrmovl %#04x, %%eax\n", tmp);
            } 
            if(quad->arg2->type == 'I')
            {
                tmp = *(int*)quad->arg2->value;
                printf("irmovl $%d, %%ecx\n", tmp);
            }
            else if(quad->arg2->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg2->value);
                printf("mrmovl %#04x, %%ecx\n", tmp);
            }
            printf("addl %%ecx, %%eax\n");
            tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
            printf("rmmovl %%eax, %#04x\n", tmp);
        break;
        case Mo:
            if(quad->arg1->type == 'I')
            {
                tmp = *(int*)quad->arg1->value;
                printf("irmovl $%d, %%eax\n", tmp);
            }
            else if(quad->arg1->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg1->value);
                printf("mrmovl %#04x, %%eax\n", tmp);
            } 
            if(quad->arg2->type == 'I')
            {
                tmp = *(int*)quad->arg2->value;
                printf("irmovl $%d, %%ecx\n", tmp);
            }
            else if(quad->arg2->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg2->value);
                printf("mrmovl %#04x, %%ecx\n", tmp);
            }
            printf("subl %%ecx, %%eax\n");
            tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
            printf("rmmovl %%eax, %#04x\n", tmp);
        break;
        case Mu:
            if(quad->arg1->type == 'I')
            {
                tmp = *(int*)quad->arg1->value;
                printf("irmovl $%d, %%ebx\n", tmp);
            }
            else if(quad->arg1->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg1->value);
                printf("mrmovl %#04x, %%ebx\n", tmp);
            } 
            if(quad->arg2->type == 'I')
            {
                tmp = *(int*)quad->arg2->value;
                printf("irmovl $%d, %%ecx\n", tmp);
            }
            else if(quad->arg2->type == 'V')
            {
                tmp = memorystart + Env_get_value(variablesOffset, (char*)quad->arg2->value);
                printf("mrmovl %#04x, %%ecx\n", tmp);
            }
            printf("irmovl $0, %%edx\n");//somme
            printf("irmovl $0, %%eax\n");//counter
            printf("loop%d: addl %%ebx, %%edx\n", loopCounter);
            printf("iaddl 1, %%eax\n"); //incrementation counter
            printf("pushl %%eax\n");
            printf("subl %%ecx, %%eax\n");
            printf("popl %%eax\n");
            printf("jl loop%d\n", loopCounter);
            loopCounter = loopCounter + 1;            
            tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
            printf("rmmovl %%edx, %#04x\n", tmp);
        break;
    }
}