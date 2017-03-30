#include "Ast.h"


struct Ast* Ast_init(int nodetype, int ope, struct Ast* left, struct Ast* right)
{
    struct Ast* ast = malloc(sizeof(struct Ast));
    ast->nodetype = nodetype;
    ast->left = left; 
    ast->right = right;
    int* tmp = malloc(sizeof(int));
    *tmp = ope;
    ast->value=tmp;
    //printf("%p Tree %c: %d (%p, %p)\n", ast, nodetype, ope, left, right);    
    return ast;
}

struct Ast* Ast_init_leaf(int nodetype, void *value)
{
    struct Ast* ast = malloc(sizeof(struct Ast));
    //printf("%p Leaf %c: ", ast, nodetype);    
    ast->nodetype = nodetype;
    ast->left = 0; 
    ast->right = 0;
    ast->value = value;
    //printf("\n");
    return ast;
}

