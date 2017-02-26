#ifndef AST_H
#define AST_H

#include <stdlib.h>

#include "Env.h"

struct Ast{
    int nodetype;
    struct Ast* left;
    struct Ast* right;
};


struct AstValue{
    int nodetype;
    void* value;
};

struct Ast* Ast_init(int nodetype, struct Ast* left,struct Ast *right);
struct Ast* AstValue_init(int nodetype, void* value);

void Ast_run(struct Ast* ast, Env* env);

void Ast_free(struct Ast* ast);

#endif 