#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdlib.h>
#include <string.h>

#include "Variable.h"
#include "Function.h"
#include "Env.h"
#include "Ast.h"
#include "./../ppinterpret.tab.h"
#include "Pascal.h"

struct Variable* Pascal_Semantic_Analysis( struct Stack* stack, struct Env* env, struct FuncList* functions, struct Ast* ast);


#endif // SEMANTIC_H
