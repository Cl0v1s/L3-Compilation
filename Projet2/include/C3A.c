#include "C3A.h"

void C3A_run(struct QuadList* list, struct EnvC3A* global)
{
    struct Stack* stack = Stack_init();
    struct Quad* current = list->start;
    struct Quad* next;
    do
    {
        current = C3A_eval(current, global, list, stack);
        Stack_print(stack);
        if( current == 0)
            return;
    }
    while(list->start != list->end && current != 0);

}

struct Quad* C3A_eval(struct Quad* quad, struct EnvC3A* env, struct QuadList* list, struct Stack* stack)
{
    int tmp;
    int tmp1;
    int tmp2;
    int adr;
    int size;
    struct Quad* next;
    //printf("Eval node %p %s | %p %p\n",quad,  quad->address, list->start, list->start->address);
    switch(quad->operation)
    {
        case And:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0) == true && Value_get(quad->arg2, env, stack, &adr, &size, 0) == true;
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Or:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0) == true || Value_get(quad->arg2, env, stack, &adr, &size, 0) == true;
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Lt:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0) < Value_get(quad->arg2, env, stack, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Not:
            tmp = !Value_get(quad->arg1, env, stack, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Pl:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0) + Value_get(quad->arg2, env, stack, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Mo:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0) - Value_get(quad->arg2, env, stack, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Mu:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0) * Value_get(quad->arg2, env, stack, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Af:
            tmp = Value_get(quad->arg2, env, stack, &adr, &size, 0);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;
        case Afc:
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, tmp1, tmp);
            EnvC3A_set_value(env, quad->destination, tmp1);
            return quad->next;

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
            tmp = Value_get(quad->arg1, env, stack, &adr, &size, 0);
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
