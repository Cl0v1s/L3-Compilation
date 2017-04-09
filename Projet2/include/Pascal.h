//
// Created by clovis on 30/03/17.
//

#ifndef COMPILATION_PASCAL_H
#define COMPILATION_PASCAL_H

#include <stdlib.h>
#include <string.h>

#include "Variable.h"
#include "Function.h"
#include "Env.h"
#include "Ast.h"
#include "./../ppinterpret.tab.h"

#define GetARR -1
#define CallFUNC -2
#define AfInd -3


struct Variable* Pascal_run(struct Stack* stack, struct Env* global, struct FuncList* functions, struct Ast* ast, struct Env* local);

void Pascal_semantic(int cond, char* error);

void Pascal_semanticFunctions(struct FuncList* functions);




#endif //COMPILATION_PASCAL_H
