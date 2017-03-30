#include "Function.h"



struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct Env* list, struct Type* type)
{
    struct FuncDisclaimer* res = malloc(sizeof(struct FuncDisclaimer));
    res->name = strdup(name);
    res->args = list;
    res->type = type;
    return res;
}

struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct Env* list, struct Ast* ast)
{
    struct Func* res = malloc(sizeof(struct Func));
    res->disclaimer = disclaimer;
    res->vars = list;
    res->ast = ast;
    return res;
}

