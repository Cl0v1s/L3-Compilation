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
    printf("%p Tree %c: %d (%p, %p)\n", ast, nodetype, ope, left, right);    
    return ast;
}

struct Ast* Ast_init_leaf(int nodetype, void *value)
{
    struct Ast* ast = malloc(sizeof(struct Ast));
    printf("%p Leaf %c: ", ast, nodetype);    
    ast->nodetype = nodetype;
    ast->left = 0; 
    ast->right = 0;
    if(nodetype == 'I')
    {
        int* tmp = malloc(sizeof(int));
        memcpy(tmp, value, sizeof(int));
        ast->value=tmp;
        printf("%d", *((int*)ast->value));
    }
    else if(nodetype == 'V')
    {
        int len = strlen((char*)value) + 1;
        char* tmp = malloc(len*sizeof(char));
        memcpy(tmp, value, len*sizeof(char));
        ast->value = tmp;
        printf("%s", ((char*)ast->value));        
    }
    printf("\n");
    return ast;
}

void Ast_run(struct Ast* ast, Env *env)
{
    
}