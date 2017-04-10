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
        printf("(%s (%lu) : [",global->names[i], key);
        for(int u = 0; u <stack->size[index]; u++)
        {
            printf("%d,", stack->values[stack->adr[index]+u]);
        }
        printf("] )\n");
    }
    printf("Watch log to get var names.\n");

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

void C3A_replace(struct EnvC3A* env, struct Stack* stack,  char* key, int value)
{
    if(EnvC3A_key_exists(env, key) == true)
    {
        int tmp = EnvC3A_get_value(env, key);
        Stack_deref(stack, tmp);
    }
    Stack_ref(stack, value);
    EnvC3A_set_value(env, key, value);
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
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0) == true && Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0) == true;
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Or:
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0) == true || Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0) == true;
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Lt:
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0) < Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Not:
            tmp = !Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Pl:
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0) + Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Mo:
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0) - Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Mu:
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0) * Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Af:
            if(quad->arg2->type == 'V') {
                used = C3A_select(global, local, (char *) quad->arg2->value);
                tmp = EnvC3A_get_value(used, (char *) quad->arg2->value);
                //tmp = Stack_copy(stack, tmp);
                used = C3A_select(global, local, quad->destination);
                C3A_replace(used, stack, quad->destination, tmp);
            }
            else
            {
                tmp = Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
                tmp1 = Stack_push(stack, 1);
                Stack_setValue(stack, stack->adr[tmp1], tmp);
                used = C3A_select(global, local, quad->destination);
                C3A_replace(used, stack, quad->destination, tmp1);
            }
            return quad->next;
        case Afc:
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case AfInd:
            // valeur a allouer
            value = Value_create('V', quad->destination);
            tmp = Value_get(value, stack, global, local, used, &pos, &adr, &size, 0);
            Value_delete(value);
            // index auquel allouer
            tmp2 = Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            //index du tableau
            Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0);
            //allocation
            tmp1 = Stack_setValue_expand(stack, pos, tmp2, tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, (char*)quad->arg1->value, tmp1);
            return quad->next;
        case Ind:
            // index de la valeur
            tmp2 = Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            // valeur
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, tmp2);
            //printf("%s <- %d\n", quad->destination, tmp);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            used = C3A_select(global, local, quad->destination);
            C3A_replace(used, stack, quad->destination, tmp1);
            return quad->next;
        case Param:
            tmp = Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
            tmp1 = Stack_push(stack, 1);
            Stack_setValue(stack, stack->adr[tmp1], tmp);
            Stack_ref(stack, tmp1);
            EnvC3A_set_value(params, (char*)quad->arg1->value, tmp1);
            return quad->next;
        case Call:
            //printf("CALLLLLLL\n");
            tmp = Value_get(quad->arg2, stack, global, local, used, &pos, &adr, &size, 0);
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
            EnvC3A_free(localprim, stack);
            EnvC3A_free(paramprim, stack);
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
            tmp = Value_get(quad->arg1, stack, global, local, used, &pos, &adr, &size, 0);
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
