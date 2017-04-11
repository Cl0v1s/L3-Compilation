#include "C3A.h"

// indicateur de profondeur d'appel de fonction (utilisé pour déterminer quel environnement utilise par defaut)
int deep = 0;

void C3A_print(struct EnvC3A* global, struct Stack* stack)
{
    unsigned long key;
    int index;
    printf("\n=============\nResults:\n");
    for(int i = 0; i < global->length; i++)
    {
        key = global->keys[i];
        index = global->values[i];
        printf("(%s (%lu) : %d)\n", global->names[i], key, index);
    }
    Stack_print(stack);

}

struct EnvC3A* C3A_select(struct EnvC3A* global, struct EnvC3A* local, char* value)
{

    struct EnvC3A* used = 0;
    if(deep <= 0 )
        used = global;
    else used = local;
    if(global != 0 && EnvC3A_key_exists(global, value))
        used = global;
    else if(local != 0 && EnvC3A_key_exists(local, value))
        used = local;
    return used;
}

void C3A_run(struct QuadList* list, struct Quad* start, struct Stack* stack, struct EnvC3A* global,struct EnvC3A* local, struct EnvC3A* params)
{
    struct Quad* current = list->start;
    if(start != 0)
    {
        current = start;
    }
    struct Quad* next;
    do
    {
        current = C3A_eval(current, list, stack, global, local, params);
#ifdef DEBUG
        Stack_print(stack);
#endif
        if( current == 0)
            return;
    }
    while(list->start != list->end && current != 0);

}

struct Quad* C3A_eval(struct Quad* quad,  struct QuadList* list, struct Stack* stack, struct EnvC3A* global,struct EnvC3A* local, struct EnvC3A* params)
{
    int tmp;
    int tmp1;
    int tmp2;
    int adr;
    int size;
    int pos;
    struct Value* value;
    struct Quad* next;
    struct EnvC3A* used;
    struct EnvC3A* tmp3;
    struct EnvC3A* tmp4;
    //printf("Eval node %d\n", quad->operation);
    switch(quad->operation)
    {
        case And:
            tmp = Value_get(quad->arg1, stack, global, local, used) == true && Value_get(quad->arg2, stack, global, local, used) == true;
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Or:
            tmp = Value_get(quad->arg1, stack, global, local, used) == true || Value_get(quad->arg2, stack, global, local, used) == true;
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Lt:
            tmp = Value_get(quad->arg1, stack, global, local, used) < Value_get(quad->arg2, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Not:
            tmp = !Value_get(quad->arg1, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Pl:
            tmp = Value_get(quad->arg1, stack, global, local, used) + Value_get(quad->arg2, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Mo:
            tmp = Value_get(quad->arg1, stack, global, local, used) - Value_get(quad->arg2, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Mu:
            tmp = Value_get(quad->arg1, stack, global, local, used) * Value_get(quad->arg2, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Af:
            tmp = Value_get(quad->arg2, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case Afc:
            tmp = Value_get(quad->arg1, stack, global, local, used);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp);
            return quad->next;
        case AfInd:
            // valeur a allouer
            value = Value_create('V', quad->destination);
            tmp = Value_get(value, stack, global, local, used);
            Value_delete(value);
            // index auquel allouer
            tmp2 = Value_get(quad->arg2, stack, global, local, used);
            //index du tableau
            tmp1 = Value_get(quad->arg1, stack, global, local, used);
            //allocation
            tmp1 = Stack_setValue_expand(stack, tmp1, tmp2, tmp);
            used = C3A_select(global, local, (char*)quad->arg1->value);
            EnvC3A_set_value(used, (char*)quad->arg1->value, tmp1);
            return quad->next;
        case Ind:
            // index de la valeur
            tmp2 = Value_get(quad->arg2, stack, global, local, used);
            // valeur
            tmp = Value_get(quad->arg1, stack, global, local, used);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_getValue(stack, stack->adr[tmp]+tmp2);
            used = C3A_select(global, local, quad->destination);
            EnvC3A_set_value(used, quad->destination, tmp1);
            return quad->next;
        case Param:
            tmp = Value_get(quad->arg2, stack, global, local, used);
            EnvC3A_set_value(params, (char*)quad->arg1->value, tmp);
            return quad->next;
        case Call:
            //printf("CALLLLLLL\n");
            tmp = Value_get(quad->arg2, stack, global, local, used);
            next = QuadList_search(list, quad->destination);
            if(next == 0)
            {
                printf("L'adresse '%s' est introuvable.\n", quad->destination);
                exit(1);
            }
            //ca1
            struct EnvC3A* localprim = EnvC3A_copy(params);
            //ca2
            for(int i = 0; i < tmp; i++)
            {
                EnvC3A_pop(params, 0,0);
            }
            //ca3
            struct EnvC3A* paramprim = EnvC3A_init();
            //ca4
            deep++;
            C3A_run(list, next, stack,  global, localprim, paramprim);
            deep--;
            EnvC3A_free(localprim);
            EnvC3A_free(paramprim);
            return quad->next;
        case Ret:
            return 0;
        case Jp:
            //printf("Jp %s\n", quad->address);
            next = QuadList_search(list, quad->destination);
            //printf("next: %p\n", next);
            if(next == 0)
            {
                printf("L'adresse '%s' est introuvable.\n", quad->destination);
                exit(1);
            }
            return next;
        case Jz:
            tmp = Value_get(quad->arg1, stack, global, local, used);
            if(tmp != 0)
            {
                return quad->next;
            }
            next = QuadList_search(list, quad->destination);
            if(next == 0)
            {
                printf("L'adresse '%s' est introuvable.\n", quad->destination);
                exit(1);
            }
            return next;
        case St:
            return 0;
        case Sk:
            return quad->next;
        default:
            return 0;
    }
}
