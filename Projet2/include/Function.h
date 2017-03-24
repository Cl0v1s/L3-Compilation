#ifndef FUNCTION_H
#define FUNCTION_H

#include "Variable.h"
#include "AST.h"

struct Type
{
	int type;
	struct Type* child;	
};

struct Args
{
	struct Type** types;
	int length;	
};

struct Func
{
	char* name;
	struct Args* args;
	struct Ast* ast;
};

struct Func* Func_init(char* name, struct Args* args, struct Ast* ast):

void Func_exec(struct Func* func, struct Env* env, struct Env* param);

struct Type* Type_init(int type, struct Type* child);

char Type_check(struct Variable* var);

struct Args* Args_init();

void Args_add(struct Type* type);

char Args_check(struct Variable* list);

#endif 