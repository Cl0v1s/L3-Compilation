//
// Created by quentin on 05/04/17.
//

#ifndef COMPILATION_COMPPASCAL_H
#define COMPILATION_COMPPASCAL_H


#include <stdio.h>

#include "Ast.h"
#include "Function.h"
#include "Pascal.h"
#include "./../ppinterpret.tab.h"

/**
* Compile un programe IMP en programme C3A
* imp: programme IMP
**/
void P_Compile_C3A(struct FuncList* functions, struct Ast* ast);


#endif //COMPILATION_COMPPASCAL_H