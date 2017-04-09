#include "C3A.h"


void C3A_replace(struct EnvC3A* env, struct Stack* stack,  char* key, int value)
{
    if(EnvC3A_key_exists(env, key) == true)
    {
        int tmp = EnvC3A_get_value(env, key);
        Stack_remove(stack, tmp);
    }
    EnvC3A_set_value(env, key, value);
}

void C3A_run(struct QuadList* list, struct Quad* start, struct EnvC3A* global,struct EnvC3A* local, struct EnvC3A* params)
{
    struct Stack* stack = Stack_init();
    struct Quad* current = list->start;
    if(start != 0)
    {
        current = start;
    }
    struct Quad* next;
    do
    {
        current = C3A_eval(current, list, stack, global, local, params);
        Stack_print(stack);
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
    //printf("Eval node %p %s | %p %p\n",quad,  quad->address, list->start, list->start->address);
    switch(quad->operation)
    {
        case And:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0) == true && Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0) == true;
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Or:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0) == true || Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0) == true;
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Lt:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0) < Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Not:
            tmp = !Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Pl:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0) + Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Mo:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0) - Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Mu:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0) * Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Af:
            tmp = Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Afc:
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case AfInd:
            // valeur a allouer
            value = Value_create('V', quad->destination);
            tmp = Value_get(value, global, stack, &pos, &adr, &size, 0);
            Value_delete(value);
            // index auquel allouer
            tmp2 = Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            //index du tableau
            Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0);
            //allocation
            tmp1 = Stack_setValue_expand(stack, pos, tmp2, tmp);
            C3A_replace(global, stack, (char*)quad->arg1->value, tmp1);
            return quad->next;
        case Ind:
            // index de la valeur
            tmp2 = Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            // valeur
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, tmp2);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            C3A_replace(global, stack, quad->destination, tmp1);
            return quad->next;
        case Param:
            tmp = Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
            EnvC3A_set_value(params, (char*)quad->arg1->value, tmp);
            return quad->next;
        case Call:
            tmp = Value_get(quad->arg2, global, stack, &pos, &adr, &size, 0);
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
                Env_C3A_pop(params, 0,0);
            }
            //ca3
            struct EnvC3A* paramprim = EnvC3A_init();
            //ca4
            C3A_run(list, next, global, localprim, paramprim);
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
            tmp = Value_get(quad->arg1, global, stack, &pos, &adr, &size, 0);
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
