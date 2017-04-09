#include "Function.h"



struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct Env* vars, struct Ast* ast)
{
    struct Func* res = malloc(sizeof(struct Func));
    res->disclaimer = disclaimer;
    res->vars = vars;
    res->ast = ast;
    return res;
}

struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct Env* list, struct Type* type)
{
    struct FuncDisclaimer* res = malloc(sizeof(struct FuncDisclaimer));
    res->name = strdup(name);
    res->args = list;
    res->type = type;
    return res;
}



struct FuncList* FuncList_init()
{
    struct FuncList* fnc = malloc(sizeof(struct FuncList));
    fnc->list = malloc(0);
    fnc->length = 0;
    return fnc;
}

void FuncList_append(struct FuncList* funcs, struct Func* func)
{
    struct Func** list = malloc((funcs->length+1)*sizeof(struct Func*));
    memcpy(list, funcs->list, funcs->length*sizeof(struct Func*));
    list[funcs->length] = func;
    free(funcs->list);
    funcs->list = list;
    funcs->length = funcs->length + 1;
}

struct Func* FuncList_search(struct FuncList* funcs, char* name)
{
    struct Func* current;
    for(int i = 0; i < funcs->length; i++)
    {
        current = funcs->list[i];
        if(strcmp(current->disclaimer->name, name) == 0)
            return current;
    }
    return 0;
}


int FuncDiclaimer_check(struct FuncDisclaimer* d1, struct FuncDisclaimer* d2)
{
    if(Type_check_strict(d1->type, d2->type) == false)
        return false;
    if(d1->args->length != d2->args->length)
        return false;
    for(int i = 0; i<d1->args->length; i++)
    {
        if(Type_check_strict(d1->args->values[i]->type, d2->args->values[i]->type) == false)
            return false;
    }
    return true;
}

