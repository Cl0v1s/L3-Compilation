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

// Argt
struct Arg
{
	char* name;
	struct Type* type;
};

// L_argt
struct ArgList
{
	int length;
	struct Arg** args;
};

// D_entf / D_entp (type VOID)
struct FuncDisclaimer
{
	char* name;
	struct ArgList* args;
	struct Type* type;
};

// D
struct Func
{
    struct FuncDisclaimer* disclaimer;
    struct ArgList* vardisclaimer;
    struct Ast* ast;
};

struct Type* Type_init(int type, struct Type* child);

struct Arg* Arg_init(char* name, struct Type* type);

struct ArgList* ArgList_init();

void ArgList_append(struct ArgList* list, struct Arg* arg);

struct FuncDisclaimer* FuncDisclaimer_init(char* name, struct ArgList* list, struct Type* type);

struct Func* Func_init(struct FuncDisclaimer* disclaimer, struct ArgList* list, struct Ast* ast);

#endif 