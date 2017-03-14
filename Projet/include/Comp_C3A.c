#include "Comp_C3A.h"
int loopCounter = 0;

int Comp_C3A_countInstructions(struct QuadList* list)
{
    int res = 0; //on considère que toutes les instructions font 6 octets
    struct Quad* current = list->start;
    do
    {
        if( current == 0)
            break;
        switch(current->operation)
        {
            case Afc:
            case Af:
                res = res + 6*2;
            break;
            case Pl:
            case Mo:
                res = res + 6*4;
            break;
            case Sk:
            case St:
            case Jp:
                res = res + 6*1;
            break;
            case Jz:
                res = res + 6*3;
            break;
            case Mu:
                res = res + 6*23;
            break;
        }
        current = current->next;
    }
    while(list->start != list->end && current != 0);
    res = res + res%4;
    return res;
}


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
            if(Env_key_exists(env, current->destination) == false)
            {
                Env_set_value(env, current->destination, offset);
                offset = offset + 4;
            }
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
    int memorystart = Comp_C3A_countInstructions(list);
    int memoryend;
    Env* variablesOffset = Comp_C3A_declareVariables(list, &memoryend);
    memoryend = memorystart+memoryend+stacksize;
    //printf("prog: 0x00 memory: %#04x stack %#04x\n\n", memorystart, memoryend);
    printf("irmovl %#04x, %%esp\n", memoryend);//on règle le stack après la mémoire
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
    if(quad->address != 0)
        printf("%s:", quad->address);
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

            //gestion du cas ou le deuxieme argument est negatif
            //on inverse le signe des deux arguments
            printf("isubl 0, %%ecx\n");
            printf("jge _y86loopcompare%d\n", loopCounter);
            printf("pushl %%ebx\n");            
            printf("irmovl 0, %%ebx\n");
            printf("subl %%ecx, %%ebx\n");
            printf("rrmovl %%ebx, %%ecx\n");
            printf("popl %%ebx\n");
            printf("pushl %%ecx\n");
            printf("irmovl 0, %%ecx\n");
            printf("subl %%ebx, %%ecx\n");
            printf("rrmovl %%ecx, %%ebx\n");
            printf("popl %%ecx\n");
            
            //gestion de la multiplication à proprement parleri
            printf("_y86loopcompare%d: irmovl $0, %%edx\n", loopCounter);//somme
            printf("irmovl $0, %%eax\n");//counter
            printf("_y86loop%d: addl %%ebx, %%edx\n", loopCounter);
            printf("iaddl 1, %%eax\n"); //incrementation counter
            printf("pushl %%eax\n");
            printf("subl %%ecx, %%eax\n");
            printf("popl %%eax\n");
            printf("jl _y86loop%d\n", loopCounter);
            loopCounter = loopCounter + 1;            
            tmp = memorystart+Env_get_value(variablesOffset, quad->destination);
            printf("rmmovl %%edx, %#04x\n", tmp);
        break;
        case Sk:
            printf("nop\n");
            break;
        case St:
            printf("halt\n");
            break;
        case Jp:
            printf("jmp %s\n", quad->destination);
            break;
        case Jz:
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
            printf("isubl 0, %%eax\n");
            printf("je %s\n", quad->destination);
            break;
    }
}