#include "IMP.h"


struct Ast* Ast_IMP_init_leaf(int nodetype, void* value)
{
    if(nodetype == 'I')
    {
        int* tmp = malloc(sizeof(int));
        memcpy(tmp, value, sizeof(int));
        value=tmp;
    }
    else if(nodetype == 'V')
    {
        int len = strlen((char*)value) + 1;
        char* tmp = malloc(len*sizeof(char));
        memcpy(tmp, value, len*sizeof(char));
        value = tmp;
    }
    return Ast_init_leaf(nodetype, value);
}


int Ast_IMP_run(struct Ast* ast, Env *env)
{
    // Si AST est nul, on retourne 0 sans l'executer
    if(ast == 0)
    {
        return 0;
    }
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
    //printf("Running ope %d\n", ope);
    int tmp, tmp1, tmp2;
    char* key;
    switch(ope)
    {
        case Sk:
            return 1;
        case Se:
            Ast_IMP_run(ast->left, env);
            Ast_IMP_run(ast->right, env);
            return 1;
        case Af:
            key = (char*)ast->left->value;
            tmp = Ast_IMP_run(ast->right, env);
            Env_set_value(env, key, tmp);
            printf("%s <- %d\n", key, tmp);
            return 1;
        case If:
            tmp = Ast_IMP_run(ast->left, env);
            if(tmp)
            {
                return Ast_IMP_run(ast->right->left, env);                
            }
            else
            {
                return Ast_IMP_run(ast->right->right, env);
            }
            return 1;
        case Wh:
            tmp = Ast_IMP_run(ast->left, env);
            //printf("While\n");
            while(tmp)
            {
                Ast_IMP_run(ast->right, env);
                tmp = Ast_IMP_run(ast->left, env);
            }
            return 1;
        case Pl:
            tmp1 = Ast_IMP_run(ast->left, env);
            tmp2 = Ast_IMP_run(ast->right, env);
            tmp =  tmp1 + tmp2 ;
            //printf("%d = %d + %d\n", tmp, tmp1, tmp2);
            return tmp;
        case Mo:
            return Ast_IMP_run(ast->left, env) - Ast_IMP_run(ast->right, env); 
        case Mu:
            return Ast_IMP_run(ast->left, env) * Ast_IMP_run(ast->right, env);                  
        default:
            printf("Instruction Non reconnue\n");
        break;
    }
}
