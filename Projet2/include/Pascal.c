//
// Created by clovis on 30/03/17.
//

#include "Pascal.h"


struct Variable* Pascal_run(struct Env* env, struct FuncList* functions, struct Ast* ast)
{
    if(TypeSystem_isInit() == false)
        TypeSystem_init();
    char nodeType = ast->nodetype;
    if(nodeType == 'C') // commandes
    {

        return 0;
    }
    else if(nodeType == 'E') // expressions
    {
        int ope = *(int*)ast->value;
        int tmp;
        struct Variable* tmp1;
        struct Variable* tmp2;
        switch(ope)
        {
            case Pl:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = Variable_get(tmp1) + Variable_get(tmp2);
                tmp1 = Variable_init(Type_INT);
                Variable_set(tmp1, tmp);
                return tmp1;
            case Mo:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = Variable_get(tmp1) - Variable_get(tmp2);
                tmp1 = Variable_init(Type_INT);
                Variable_set(tmp1, tmp);
                return tmp1;
            case Mu:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = Variable_get(tmp1) * Variable_get(tmp2);
                tmp1 = Variable_init(Type_INT);
                Variable_set(tmp1, tmp);
                return tmp1;
            case Or:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = false;
                if(Variable_get(tmp1) == true || Variable_get(tmp2) == true)
                    tmp = true;
                tmp1 = Variable_init(Type_BOOL);
                Variable_set(tmp1, tmp);
                return tmp1;
            case Lt:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = false;
                if(Variable_get(tmp1) < Variable_get(tmp2))
                    tmp = true;
                tmp1 = Variable_init(Type_BOOL);
                Variable_set(tmp1, tmp);
                return tmp1;
            case Eq:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = false;
                if(Variable_get(tmp1) == Variable_get(tmp2))
                    tmp = true;
                tmp1 = Variable_init(Type_BOOL);
                Variable_set(tmp1, tmp);
                return tmp1;
            case And:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp2 = Pascal_run(env, functions, ast->right);
                tmp = false;
                if(Variable_get(tmp1) == true && Variable_get(tmp2) == true)
                    tmp = true;
                tmp1 = Variable_init(Type_BOOL);
                Variable_set(tmp1, tmp);
                return tmp1;
            case Not:
                tmp1 = Pascal_run(env, functions, ast->left);
                tmp = !Variable_get(tmp1);
                tmp1 = Variable_init(Type_BOOL);
                Variable_set(tmp1, tmp);
                return tmp1;
            case NewAr:
                tmp1 = Variable_init()

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

