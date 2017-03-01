#include "C3A.h"

void C3A_run(struct QuadList* list, Env* env)
{
    struct Quad* current = list->start;
    do
    {
        if(C3A_eval(current, env, list) == false)
            return;
        current = current->next;
    }
    while(list->start != list->end && current != 0);

}

int C3A_eval(struct Quad* quad, Env* env, struct QuadList* list)
{
    int tmp;
    struct Quad* next;
    switch(quad->operation)
    {
        case Pl:
            tmp = Value_get(quad->arg1, env) + Value_get(quad->arg2, env);
            Env_set_value(env, quad->destination, tmp);
            return true;
        case Mo:
            tmp = Value_get(quad->arg1, env) - Value_get(quad->arg2, env);
            Env_set_value(env, quad->destination, tmp);
            return true;
        case Mu:
            tmp = Value_get(quad->arg1, env) * Value_get(quad->arg2, env);
            Env_set_value(env, quad->destination, tmp);
            return true;
        case Af:
            tmp = Value_get(quad->arg2, env);
            Env_set_value(env, quad->destination, tmp);
            return true; 
        case Afc:
            tmp = Value_get(quad->arg1, env);
            Env_set_value(env, quad->destination, tmp);
            return true;
        case Jp:
            next = QuadList_search(list, quad->destination);
            if(next == 0)
            {
                printf("L'adresse '%s' est introuvable.\n", quad->destination);
                exit(1);
            }
            quad->next = next;
            return true;
        case Jz:
            tmp = Value_get(quad->arg1, env);
            if(tmp != 0)
                return true;
            next = QuadList_search(list, quad->destination);
            if(next == 0)
            {
                printf("L'adresse '%s' est introuvable.\n", quad->destination);
                exit(1);
            }
            quad->next = next;
            return true;
        case St:
            return false;
        case Sk:
        default:
            return true;
    }
}

