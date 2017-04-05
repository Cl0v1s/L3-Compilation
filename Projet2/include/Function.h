#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <string.h>

#include "Env.h"
#include "Variable.h"



// D_entf / D_entp (type VOID)
struct FuncDisclaimer
{
	char* name;
	struct Env* args;
	struct Type* type;
};

// D
struct Func
{
    struct FuncDisclaimer* disclaimer;
    struct Env* vars;
    struct Ast* ast;
};

struct FuncList
{
	struct Func** list;
	int length;
};

struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct Env* vars, struct Ast* ast);


struct FuncList* FuncList_init();

void FuncList_append(struct FuncList* funcs, struct Func* func);

struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct Env* args, struct Type* type);

struct Func* FuncList_search(struct FuncList* funcs, char* name);


#endif
