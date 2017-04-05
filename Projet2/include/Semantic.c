#include "Semantic.h"

struct Variable* Pascal_Semantic_Analysis( struct Stack* stack, struct Env* env, struct FuncList* functions, struct Ast* ast)
{
    // Initializing the type system
    if(TypeSystem_isInit() == false)
        TypeSystem_init();
    char nodeType = ast->nodetype;

    /** Commands **/
    if(nodeType == 'C')
    {
        int ope = *(int*)ast->value;
        int tmp;
        struct Variable* tmp1;
        struct Variable* tmp2;
        struct Type* tmp3;
        switch(ope) {
            // Separator
            case Se:
                Pascal_run(stack, env, functions, ast->left);
                Pascal_run(stack, env, functions, ast->right);
                break;
            // Affectation
            case Af:
                tmp1 = Pascal_run(stack, env, functions, ast->left);
                tmp2 = Pascal_run(stack, env, functions, ast->right);
                if(Type_check(tmp1->type, tmp2->type) == false)
                {
                    printf("Cant affect non-identical types.\n");
                    exit(-1);
                }
                if(tmp1->type != ARRAY)
                    Variable_set(tmp1, Variable_get(tmp2));
                else
                    Variable_arrayCopy(stack, tmp1, tmp2);
                break;
            // Skip
            case Sk:
                break;
            // If
            case If:
                tmp1 = Pascal_run(stack, env, functions, ast->left);
                if(tmp1->type->type == ARRAY)
                {
                    printf("Array variable cant be checked as boolean.\n");
                    exit(-1);
                }
                if(Variable_get(tmp1) == true)
                {
                    Pascal_run(stack, env, functions, ast->right->left);
                } else
                {
                    Pascal_run(stack, env, functions, ast->right->right);
                }
                break;
            case Wh:
                tmp1 = Pascal_run(stack, env, functions, ast->left);
                if(tmp1->type->type == ARRAY)
                {
                    printf("Array variable cant be checked as boolean.\n");
                    exit(-1);
                }
                while(Variable_get(tmp1) == true)
                {
                    Pascal_run(stack, env, functions, ast->right);
                    tmp1 = Pascal_run(stack, env, functions, ast->left);
                    if(tmp1->type->type == ARRAY)
                    {
                        printf("Array variable cant be checked as boolean.\n");
                        exit(-1);
                    }
                }
                break;
        }
        return 0;
    }
    else if(nodeType == 'E') // expressions
    {
        int ope = *(int*)ast->value;
        int tmp;
        struct Type* tp1;
        struct Type* tp2;
        struct Variable* tmp1;
        struct Variable* tmp2;
        struct Type* tmp3;
        switch(ope)
        {
            // Add
            case Pl:
            // Substract
            case Mo:
            // Multiply
            case Mu:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right)->type;
                if(Type_check(tp1, Type_INT) && Type_check(tp2, Type_INT)){
                  tmp1 = Variable_init(Type_INT);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operation "ope" on non-integer [ %s ] [ %s ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            // Or
            case Or:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right)->type;
                if(Type_check(tp1, Type_BOOL) == true && Type_check(tp2, Type_BOOL)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Or on a non-boolean [ %s ] [ %s ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case Lt:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right)->type;
                if(Type_check(tp1, tp2)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Lt on different types [ %s ] [ %s ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case Eq:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right)->type;
                if(Type_check(tp1, tp2)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Eq on different types [ %s ] [ %s ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case And:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right)->type;
                if(Type_check(tp1, Type_BOOL) && Type_check(tp2, Type_BOOL)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator And on different types [ %s ] [ %s ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case Not:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left)->type;
                if(Type_check(tp1, Type_BOOL)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Not on a non-boolean [ %s ].\n", tp1->type);
                }
            case NewAr:
                tmp3 = (struct Type*)ast->left->value;
                if(tmp3 < 0)
                {
                    printf("Cant create array of negative size.\n");
                    exit(-1);
                }
                return Variable_arrayInit(tmp3, stack, Variable_get(Pascal_run(stack, env, functions, ast->right)));
            case GetARR:
                tmp1 = Pascal_run(stack, env, functions, ast->left);
                if(tmp1->type->type != ARRAY)
                {
                    printf("Invalid operation on non-array variable.\n");
                    exit(-1);
                }
                tmp2 = Pascal_run(stack, env, functions, ast->right);
                if(tmp1->type->type == ARRAY)
                {
                    printf("Index array must be numeric.\n");
                    exit(-1);
                }
                return Variable_arrayGet(tmp1, stack, Variable_get(tmp2));



        }
    }
    else if(nodeType == 'I') // constantes
    {
        int tmp = (int)ast->value;
        struct Variable* tmp1 = Variable_init(Type_INT);
        Variable_set(tmp1, tmp);
        return tmp1;
    }
    else if(nodeType == 'B') // constantes
    {
        int tmp = (int)ast->value;
        struct Variable* tmp1 = Variable_init(Type_BOOL);
        Variable_set(tmp1, tmp);
        return tmp1;
    }
    else if(nodeType == 'V')
    {
        return Env_get_value(env, (char*)ast->value);
    }
}

// bool functionExists(FuncList* functions, Func* func){
//     if()
// }
