//
// Created by clovis on 08/04/17.
//

#include "C3A.h"

struct Env_C3A pp;

void C3A_run(struct QuadList* list, struct Env_C3A* global)
{
    Env_C3A_init(&pp);
    struct Quad* current = list->start;
    struct Quad* next;
    do
    {
        current = C3A_eval(current, global, 0, 0, list);
        if( current == 0)
            return;
    }
    while(list->start != list->end && current != 0);
}

struct Quad* C3A_eval(struct Quad* quad, struct Env_C3A* global, struct Env_C3A* local, struct Env_C3A* params, struct QuadList* list)
{
    int tmp;
    struct Quad* next;
    //printf("Eval node %p %s | %p %p\n",quad,  quad->address, list->start, list->start->address);
    switch(quad->operation)
    {
        case Pl:
            tmp = Value_get(quad->arg1, global, local, params) + Value_get(quad->arg2, global);
            //printf("%s <- %d\n", quad->destination, tmp);
            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Mo:
            tmp = Value_get(quad->arg1, global, local, params) - Value_get(quad->arg2, global);
            //printf("%s <- %d\n", quad->destination, tmp);

            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Mu:
            tmp = Value_get(quad->arg1, global, local, params) * Value_get(quad->arg2, global);
            //printf("%s <- %d\n", quad->destination, tmp);

            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Af:
            tmp = Value_get(quad->arg2, global);
            //printf("%s <- %d\n", quad->destination, tmp);

            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Afc:
            tmp = Value_get(quad->arg1, global, local, params);
            //printf("%s <- %d\n", quad->destination, tmp);

            Env_C3A_set_value(global, quad->destination, tmp);
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
            tmp = Value_get(quad->arg1, global, local, params);
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
        case And:
            tmp = false;
            if( Value_get(quad->arg1, global, local, params) != false && Value_get(quad->arg2, global) != false)
                tmp = true;
            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Or:
            tmp = false;
            if( Value_get(quad->arg1, global, local, params) != false || Value_get(quad->arg2, global) != false)
                tmp = true;
            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Lt:
            tmp = false;
            if( Value_get(quad->arg1, global, local, params) < Value_get(quad->arg2, global))
                tmp = true;
            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Not:
            tmp = true;
            if( Value_get(quad->arg1, global, local, params) != false)
                tmp = false;
            Env_C3A_set_value(global, quad->destination, tmp);
            return quad->next;
        case Param:
            Env_C3A_set_value(&pp, (char*)quad->arg1->value, Value_get(quad->arg2, global));
            break;
        case Call:
            tmp = Value_get(quad->arg2, 0);

        default:
            return 0;

    }
}