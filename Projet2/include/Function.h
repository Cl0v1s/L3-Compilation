#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <string.h>

#include "Env.h"
#include "Variable.h"

// TP
struct Type
{
	int type; // BOOL|INT|ARRAY
	struct Type* child;
};

// VarDisclaimt
struct VarDisclaim
{
	char* name;
	struct Type* type;
};

// L_VarDisclaimt
struct VarDisclaimList
{
	int length;
	struct VarDisclaim** args;
};

// D_entf / D_entp (type VOID)
struct FuncDisclaimer
{
	char* name;
	struct VarDisclaimList* args;
	struct Type* type;
};

// D
struct Func
{
    struct FuncDisclaimer* disclaimer;
    struct VarDisclaimList* vardisclaimer;
    struct Ast* ast;
};

struct Type* Type_init(int type, struct Type* child);

struct VarDisclaim* VarDisclaim_init(char* name, struct Type* type);

struct VarDisclaimList* VarDisclaimList_init();

void VarDisclaimList_append(struct VarDisclaimList* list, struct VarDisclaim* var);

struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct VarDisclaimList* list, struct Type* type);

struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct VarDisclaimList* list, struct Ast* ast);

#endif 