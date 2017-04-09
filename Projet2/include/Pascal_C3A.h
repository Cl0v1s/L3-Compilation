//
// Created by clovis on 09/04/17.
//

#ifndef L3_COMPILATION_PASCAL_C3A_H
#define L3_COMPILATION_PASCAL_C3A_H

#include <stdlib.h>
#include <stdio.h>

#include "./../ppinterpret.tab.h"

#include "Pascal.h"
#include "Env.h"
#include "Ast.h"
#include "Function.h"

void P_Compile_C3A(struct FuncList* functions, struct Ast* ast);
void P_Compile_C3A_eval(struct FuncList* functions, struct Ast* ast);

#endif //L3_COMPILATION_PASCAL_C3A_H
