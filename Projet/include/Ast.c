#include "Ast.h"

struct Ast* Ast_init(int nodetype, struct Ast* left, struct Ast* right)
{
    struct Ast* ast = malloc(sizeof(struct Ast));
    ast->nodetype = nodetype;
    ast->left = left; 
    ast->right = right;
    return ast;
}

struct Ast* AstValue_init(int nodetype, void *value)
{
    struct AstValue* ast = malloc(sizeof(struct AstValue));
    ast->nodetype = nodetype;
    ast->value = value; 
    return (struct Ast*)ast;
}

void Ast_run(struct Ast* ast, Env *env)
{
    
}