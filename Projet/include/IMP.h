#ifndef IMP_H
#define IMP_H

#include <string.h>
#include <stdio.h>

#include "Ast.h"
#include "Env.h"
#include "utils.h"
#include "../iimp.tab.h"

struct Ast* Ast_IMP_init_leaf(int nodetype, void* value);
int Ast_IMP_run(struct Ast* ast, Env *env);

#endif 