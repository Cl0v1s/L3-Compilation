//
// Created by clovis on 30/03/17.
//

#ifndef COMPILATION_PASCAL_H
#define COMPILATION_PASCAL_H

#include "Variable.h"
#include "Function.h"
#include "Env.h"
#include "Ast.h"
#include "./../ppinterpret.tab.h"

#define GetARR -1
#define CallFUNC -2

struct Ast* Pascal_Ast_init_leaf(int nodetype, int value);

struct Variable* Pascal_run(struct Stack* stack, struct Env* global, struct FuncList* functions, struct Ast* ast, struct Env* local);

#endif //COMPILATION_PASCAL_H
