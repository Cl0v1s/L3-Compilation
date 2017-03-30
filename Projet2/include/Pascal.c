//
// Created by clovis on 30/03/17.
//

#include "Pascal.h"


int Pascal_run(struct Env* env, struct FuncList* functions, struct Ast* ast)
{
    char nodeType = ast->nodetype;
    if(nodeType == 'C') // commandes
    {

        return 0;
    }
    else if(nodeType == 'E') // expressions
    {
        int ope = *(int*)ast->value;
        int tmp;
        int tmp1;
        int tmp2;
        switch(ope)
        {
            case Pl:
                return Pascal_run(env, functions, ast->left) + Pascal_run(env, functions, ast->right);
            case Mo:
                return Pascal_run(env, functions, ast->left) - Pascal_run(env, functions, ast->right);
            case Mu:
                return Pascal_run(env, functions, ast->left) * Pascal_run(env, functions, ast->right);
            case Or:
                if(Pascal_run(env, functions, ast->left) == true || Pascal_run(env, functions, ast->right) == true)
                    return true;
                return false;
            case Lt:
                if(Pascal_run(env, functions, ast->left) < Pascal_run(env, functions, ast->right))
                    return true;
                return false;
            case Eq:
                if(Pascal_run(env, functions, ast->left) == Pascal_run(env, functions, ast->right))
                    return true;
                return false;
            case And:
                if(Pascal_run(env, functions, ast->left) == true &&  Pascal_run(env, functions, ast->right) == true)
                    return true;
                return false;
            case Not:
                if(Pascal_run(env, functions, ast->left) == true)
                    return false;
                return true;

        }
    }
    else if(nodeType == 'I' || nodeType == 'B') // constantes
    {
        return (int)ast->value;
    }
    else if(nodeType == 'V') // variables
    {
        struct Variable* v = Env_get_value(env, (char*)ast->value);
        if(v == 0)
        {
            printf("Variable %s must be declared first !\n", (char*)ast->value);
            exit(-1);
        }
        return Variable_get(v);
    }
}

