#include "Semantic.h"

struct Variable* Pascal_Semantic_Analysis( struct Stack* stack, struct Env* env, struct FuncList* functions, struct Ast* ast, struct Env* local)
{
    // Checking end of tree
    if(ast == 0)
        return 0;

    // Initializing the type system
    if(TypeSystem_isInit() == false)
        TypeSystem_init();
    char nodeType = ast->nodetype;

    /** Commands **/
    if(nodeType == 'C') // commandes
    {
        int ope = *(int*)ast->value;
        int tmp;
        struct Type* tp1;
        struct Type* tp2;
        struct Variable* tmp1;
        struct Variable* tmp2;
        struct Type* tmp3;
        struct Func* tmp4;
        struct Env* tmp5;
        struct Env* tmp7;
        struct Ast* tmp6;
        switch(ope) {
            case Se:
                Pascal_Semantic_Analysis(stack, env, functions, ast->left, local);
                Pascal_Semantic_Analysis(stack, env, functions, ast->right, local);
                break;
            case Af:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)->type;
                if(Type_check(tp1, tp2) == false)
                {
                    printf("SEMANTIC : Command Af on non-identical types [ %i ] [ %i ].\n", tp1->type, tp2->type);
                    exit(-1);
                }
                break;
            case Sk:
                break;
            case If:
                tmp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local);
                if(tmp1->type->type == ARRAY)
                {
                    printf("SEMANTIC : If condition array variable cant be checked as boolean.\n");
                    exit(-1);
                }
                // If [true] statement analysis
                    Pascal_Semantic_Analysis(stack, env, functions, ast->right->left, local);
                // If [false] statement analysis
                    Pascal_Semantic_Analysis(stack, env, functions, ast->right->right, local);
                break;
            case Wh:
                tmp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local);
                if(tmp1->type->type == ARRAY)
                {
                    printf("SEMANTIC : While condition array variable cant be checked as boolean.\n");
                    exit(-1);
                }
                /*
                while(Variable_get(tmp1) == true)
                {
                    Pascal_Semantic_Analysis(stack, env, functions, ast->right, local);
                    tmp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local);
                    if(tmp1->type->type == ARRAY)
                    {
                        printf("Array variable cant be checked as boolean.\n");
                        exit(-1);
                    }
                }
                Collector_clean(stack);
                 */
                break;
            case CallFUNC:
                // Recherche de la fonction
                tmp4 = FuncList_search(functions, ((char*)ast->left->value));
                if(tmp4 == 0)
                {
                    printf("SEMANTIC : Use of undeclared function [ %s ].\n", (char*)ast->left->value);
                    exit(-1);
                }
                // création de l'environnement local
                // Ajout des variables arguments
                tmp5 = Env_concat(tmp4->disclaimer->args, tmp4->vars);

                // Vérification de la non-collision des environnements
                if(!Env_checkEnvCollision(env, tmp5)){
                    printf("SEMANTIC : Conflict between global and local environments.\n");
                }

                // TODO: on vérfie que la variable réservée portant le nom de la fonction n'est pas redéclarée par l'user -- Pas compris :/ on voit demain

                tmp6 = ast->right;
                // Copie des valeurs des arguments dans le nouvel environnement
                for(int i = 0; i < tmp4->disclaimer->args->length; i++)
                {
                    if(tmp6->right == 0)
                    {
                        printf("SEMANTIC : Too few arguments for function call [ %s ].\n", (char*)ast->left->value);
                        exit(-1);
                    }
                    tmp1 = Pascal_Semantic_Analysis(stack, env, functions, tmp6->right,local);
                    if(Type_check(tmp1->type, Env_get_value_index(tmp4->disclaimer->args, i)->type) == false)
                    {
                        printf("SEMANTIC : Type mismatch for function call [ %s ]. Expected [ %i ] but found [ %i ].\n", (char*)ast->left->value, Env_get_value_index(tmp4->disclaimer->args, i)->type->type, tmp1->type->type);
                        exit(-1);
                    }
                    Env_set_value_index(tmp5, i, tmp1);
                    tmp6 = tmp6->left;
                }

                // Dépassement du nombre d'arguments
                if(tmp6->right != 0){
                    printf("SEMANTIC : Too much arguments for function call [ %s ]. Expected [ %i ].\n", (char*)ast->left->value, tmp4->disclaimer->args->length);
                    exit(-1);
                }
                //TODO: vérifier que la variable de retour est bien afectée (qu'il y a bien un return) -- ? Je crois que j'ai compris mais peu de temps, on verra ça demain aussi
                // execution de la fonction
                printf("Calling... %p\n", tmp4->ast);
                Pascal_Semantic_Analysis(stack, env, functions, tmp4->ast, tmp5);
                printf("Done\n");
                free(tmp5);
//                Collector_clean(stack);
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
        struct Func* tmp4;
        struct Env* tmp5;
        struct Env* tmp7;
        struct Ast* tmp6;
        switch(ope)
        {
            // Add
            case Pl:
            // Substract
            case Mo:
            // Multiply
            case Mu:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)->type;
                if(Type_check(tp1, Type_INT) && Type_check(tp2, Type_INT)){
                  tmp1 = Variable_init(Type_INT);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operation %i on non-integer [ %d ] [ %d ].\n", ope, tp1->type, tp2->type);
                  exit(-1);
                }
            // Or
            case Or:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)->type;
                if(Type_check(tp1, Type_BOOL) == true && Type_check(tp2, Type_BOOL)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Or on a non-boolean [ %d ] [ %d ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case Lt:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)->type;
                if(Type_check(tp1, tp2)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Lt on different types [ %d ] [ %d ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case Eq:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)->type;
                if(Type_check(tp1, tp2)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Eq on different types [ %d ] [ %ds ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case And:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                tp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)->type;
                if(Type_check(tp1, Type_BOOL) && Type_check(tp2, Type_BOOL)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator And on different types [ %d ] [ %d ].\n", tp1->type, tp2->type);
                  exit(-1);
                }
            case Not:
                tp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local)->type;
                if(Type_check(tp1, Type_BOOL)){
                  tmp1 = Variable_init(Type_BOOL);
                  return tmp1;
                }
                else {
                  printf("SEMANTIC : Operator Not on a non-boolean [ %d ].\n", tp1->type);
                }
            case NewAr:
                tmp3 = (struct Type*)ast->left->value;
                if(tmp3 < 0)
                {
                    printf("Cant create array of negative size.\n");
                    exit(-1);
                }
                return Variable_arrayInit(tmp3, stack, Variable_get(Pascal_Semantic_Analysis(stack, env, functions, ast->right, local)));
            case GetARR:
                tmp1 = Pascal_Semantic_Analysis(stack, env, functions, ast->left, local);
                if(tmp1->type->type != ARRAY)
                {
                    printf("SEMANTIC : Acessing array value on non-array variable.\n");
                    exit(-1);
                }
                tmp2 = Pascal_Semantic_Analysis(stack, env, functions, ast->right, local);
                if(tmp1->type->type == ARRAY)
                {
                    printf("SEMANTIC : Index array must be numeric.\n");
                    exit(-1);
                }
                return Variable_arrayGet(tmp1, stack, Variable_get(tmp2));
            case CallFUNC:
                printf("Searching to call %s\n", (char*)ast->left->value);
                tmp4 = FuncList_search(functions, ((char*)ast->left->value));
                if(tmp4 == 0)
                {
                    printf("Function not declared.\n");
                    exit(-1);
                }
                // création de l'environnement local
                // Ajout des variables arguments
                tmp5 = Env_concat(tmp4->disclaimer->args, tmp4->vars);
                // TODO: on vérifie que l'environnement global et local ne rentrent pas en collision
                
                
                // TODO: on vérfie que la variable réservée portant le nom de la fonction n'est pas redéclarée par l'user
                tmp6 = ast->right;
                // Copie des valeurs des arguments dans le nouvel environnement
                for(int i = 0; i < tmp4->disclaimer->args->length; i++)
                {
                    if(tmp6->right == 0)
                    {
                        printf("Too few arguments.\n");
                        exit(-1);
                    }
                    tmp1 = Pascal_Semantic_Analysis(stack, env, functions, tmp6->right, local);
                    if(Type_check(tmp1->type, Env_get_value_index(tmp4->disclaimer->args, i)->type) == false)
                    {
                        printf("Type mismatch.\n");
                        exit(-1);
                    }
                    Env_set_value_index(tmp5, i, tmp1);
                    tmp6 = tmp6->left;
                }
                // Ajout d'une variable portant le nom de la fonction faisant office de return
                Env_add_value(tmp5, (char*)ast->left->value, Variable_init(tmp4->disclaimer->type));
                // execution de la fonction
                printf("Calling... %p\n", tmp4->ast);
                Pascal_Semantic_Analysis(stack, env, functions, tmp4->ast, tmp5);
                printf("Done\n");
                // Récupération de la variable faisant office de return
                tmp1 = Env_get_value(tmp5, (char*)ast->left->value);
                printf("Returning value %d\n", Variable_get(tmp1));
                free(tmp5);
                tmp1->refs = 0;
                return tmp1;



        }
    }
    else if(nodeType == 'I') // constantes
    {
        int tmp = *(int*)ast->value;
        struct Variable* tmp1 = Variable_init(Type_INT);
        Variable_set(tmp1, tmp);
        return tmp1;
    }
    else if(nodeType == 'B') // constantes
    {
        int tmp = *(int*)ast->value;
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
