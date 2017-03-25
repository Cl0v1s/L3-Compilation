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

struct Arg* Arg_init(char* name, struct Type* type)
{
    struct Arg* res = malloc(sizeof(struct Arg));
    res->name = strdup(name);
    res->type = type;
    return res;
}

struct ArgList* ArgList_init()
{
    struct ArgList* res = malloc(sizeof(struct ArgList));
    res->args = malloc(0);
    res->length = 0;
    return res;
}

void ArgList_append(struct ArgList* list, struct Arg* arg)
{
    struct Arg** args = malloc((list->length+1)*sizeof(struct Arg*));
    memcpy(args, list->args, list->length*sizeof(struct Arg*));
    args[list->length] = arg;

    free(list->args);
    list->args = args;
    list->length = list->length+1;
}

struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct ArgList* list, struct Type* type)
{
    struct FuncDisclaimer* res = malloc(sizeof(struct FuncDisclaimer));
    res->name = strdup(name);
    res->args = list;
    res->type = type;
    return res;
}

struct Method* Method_init(struct FuncDisclaimer* disclaimer, struct ArgList* list, struct Ast* ast)
{
    struct Method* res = malloc(sizeof(struct Method));
    res->disclaimer = disclaimer;
    res->vardisclaimer= list;
    res->ast = ast;
    return res;
}

