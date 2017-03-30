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




struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct Env* args, struct Type* type);

struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct Env* vars, struct Ast* ast);

#endif 