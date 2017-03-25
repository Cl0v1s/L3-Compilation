#include "Function.h"

struct Type* Type_init(int type, struct Type* child)
{
    struct Type* res = malloc(sizeof(struct Type));
    res->type = type;
    if(type == INT || type == BOOL)
    {
        res->child = 0;
    }
    else 
        res->child = child;
    return res;
}

struct VarDisclaim* VarDisclaim_init(char* name, struct Type* type)
{
    struct VarDisclaim* res = malloc(sizeof(struct VarDisclaim));
    res->name = strdup(name);
    res->type = type;
    return res;
}

struct VarDisclaimList* VarDisclaimList_init()
{
    struct VarDisclaimList* res = malloc(sizeof(struct VarDisclaimList));
    res->args = malloc(0);
    res->length = 0;
    return res;
}

void VarDisclaimList_append(struct VarDisclaimList* list, struct VarDisclaim* arg)
{
    struct VarDisclaim** args = malloc((list->length+1)*sizeof(struct VarDisclaim*));
    memcpy(args, list->args, list->length*sizeof(struct VarDisclaim*));
    args[list->length] = arg;

    free(list->args);
    list->args = args;
    list->length = list->length+1;
}

struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct VarDisclaimList* list, struct Type* type)
{
    struct FuncDisclaimer* res = malloc(sizeof(struct FuncDisclaimer));
    res->name = strdup(name);
    res->args = list;
    res->type = type;
    return res;
}

struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct VarDisclaimList* list, struct Ast* ast)
{
    struct Func* res = malloc(sizeof(struct Func));
    res->disclaimer = disclaimer;
    res->vardisclaimer= list;
    res->ast = ast;
    return res;
}

