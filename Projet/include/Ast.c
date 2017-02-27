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

int Ast_run(struct Ast* ast, Env *env)
{
    if(ast->nodetype == 'V')
    {
            char* key = (char*)ast->value;
            if(Env_key_exists(env, key) == false)
            {
                printf("Impossible d'utiliser une variable non déclarée.\n");
                exit(1);
            }
            return Env_get_value(env, key);
    }
    else if(ast->nodetype == 'I')
    {
            return *(int*)ast->value;   
    }
    // On arrive ici si le noeud n'est pas une feuille
    int ope = *(int*)ast->value;
    printf("Running ope %d\n", ope);
    int tmp;
    char* key;
    switch(ope)
    {
        case Sk:
            return 1;
        case Se:
            Ast_run(ast->left, env);
            Ast_run(ast->right, env);
            return 1;
        case Af:
            key = (char*)ast->left->value;
            tmp = Ast_run(ast->right, env);
            Env_set_value(env, key, tmp);
            printf("%s <- %d\n", key, tmp);
            return 1;
        case If:
            tmp = Ast_run(ast->left, env);
            if(tmp == false)
            {
                return Ast_run(ast->right->right, env);
            }
            else 
            {
                return Ast_run(ast->right->left, env);
            }
            return 1;
        case Wh:
            tmp = Ast_run(ast->left, env);
            while(tmp!=false)
            {
                Ast_run(ast->right, env);
                tmp = Ast_run(ast->left, env);
            }
            return 1;
        case Pl:
            return Ast_run(ast->left, env) + Ast_run(ast->right, env);
        case Mo:
            return Ast_run(ast->left, env) - Ast_run(ast->right, env); 
        case Mu:
            return Ast_run(ast->left, env) * Ast_run(ast->right, env);                  
        default:
            printf("Instruction Non reconnue\n");
        break;
    }
}