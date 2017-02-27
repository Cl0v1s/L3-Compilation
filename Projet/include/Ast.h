#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>

#include "Env.h"
#include "utils.h"
#include "../iimp.tab.h"

struct Ast{
    int nodetype;
    void* value;
    struct Ast* left;
    struct Ast* right;
};

struct Ast* Ast_init(int nodetype,int ope, struct Ast* left,struct Ast *right);
struct Ast* Ast_init_leaf(int nodetype, void* value);

int Ast_run(struct Ast* ast, Env* env);

void Ast_free(struct Ast* ast);

#endif 