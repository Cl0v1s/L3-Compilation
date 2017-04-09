//
// Created by clovis on 09/04/17.
//

#include "Pascal_C3A.h"

int line = 0;
int tmpvar = 0;
int tmpjump = 0;

void P_Compile_C3A(struct FuncList* functions, struct Ast* ast)
{
    // déclaration de variables globales portant le nom des fonctions pour gérer le retour des valeurs des fonctions
    for(int i = 0; i < functions->length; i++)
    {
        printf("l%d : Afc : 0 : : %s\n", line,functions->list[i]->disclaimer->name);
        line = line + 1;
    }

    P_Compile_C3A_eval(functions, ast);

    // Ajout des différentes fonctions
    for(int i = 0; i < functions->length; i++)
    {
        printf("%s : Sk :  : : \n", functions->list[i]->disclaimer->name);
        line = line + 1;
        for(int u = 0; u < functions->list[i]->disclaimer->args->length; u++)
        {
            printf("l%d : Af : %s : _P%lu :\n", line, functions->list[i]->disclaimer->args->names[u], functions->list[i]->disclaimer->args->keys[u]);
            line++;
        }
        P_Compile_C3A_eval(functions, functions->list[i]->ast);
        printf("l%d : Ret : : :\n", line);
        line++;
    }

}

void P_Compile_C3A_eval(struct FuncList* functions, struct Ast* ast) {
    if (ast == 0)
        return;
    //printf("COMPILING %p ", ast);
    //Ast_print(ast);
    if (ast->nodetype == 'I' || ast->nodetype == 'B') {
        tmpvar = tmpvar + 1;
        printf("l%d : Afc : %d : : _TMP%d\n", line, *(int *) ast->value, tmpvar);
        line = line + 1;
        return;
    }
    if (ast->nodetype == 'V') {
        tmpvar = tmpvar + 1;
        printf("l%d : Af : _TMP%d : %s :\n", line, tmpvar, (char *) ast->value);
        line = line + 1;
        return;
    }

    // On arrive ici si le noeud n'est pas une feuille
    int ope = *(int *) ast->value;
    int tmpleft;
    int tmpright;
    struct Func* tmp4;
    struct Type *tmp1;
    struct Ast* tmp6;
    switch (ope) {
        case Pl:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Pl : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Mo:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mo : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Mu:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mu : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Eq:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mu : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            tmpleft = tmpvar;
            tmpvar++;
            printf("l%d : Not : _TMP%d :  : _TMP%d\n", line, tmpleft, tmpvar);
            line = line + 1;
            break;
        case Lt:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Lt : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case And:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : And : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Or:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Or : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Not:
            P_Compile_C3A_eval(functions, ast->left);
            tmpleft = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Not : _TMP%d : : _TMP%d\n", line, tmpleft, tmpvar);
            line = line + 1;
            break;
        case Sk:
            printf("l%d : Sk :  :  : \n", line);
            return;
        case Se:
            P_Compile_C3A_eval(functions,  ast->left);
            P_Compile_C3A_eval(functions,  ast->right);
            return;
        case Af:
            P_Compile_C3A_eval(functions,  ast->right);
            printf("l%d : Af : %s : _TMP%d : \n", line, (char*)ast->left->value, tmpvar);
            line++;
            return;
        case NewAr:
            P_Compile_C3A_eval(functions,  ast->right);
            tmpright = tmpvar;
            tmpvar++;
            // le tableau aura une taille supérieur de 1 a la taille demandée
            printf("l%d : AfInd : _TMP%d : _TMP%d : 0\n", line, tmpvar, tmpright);
            line++;
            return;
        case GetARR:
            P_Compile_C3A_eval(functions,  ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions,  ast->right);
            tmpright = tmpvar;
            tmpvar++;
            printf("l%d : Ind : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line++;
            return;
        case AfInd:
            P_Compile_C3A_eval(functions,  ast->left->left);
            tmpleft = tmpvar;
            P_Compile_C3A_eval(functions,  ast->left->right);
            tmpright = tmpvar;
            P_Compile_C3A_eval(functions,  ast->right);
            printf("l%d : AfInd : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line++;
            return;
        case If:
            tmpjump = tmpjump + 1;
            tmpleft = tmpjump;
            P_Compile_C3A_eval(functions, ast->left);
            printf("l%d : Jz : _TMP%d : : IfFalse%d\n", line, tmpvar, tmpleft);
            line = line + 1;
            P_Compile_C3A_eval(functions, ast->right->left);
            printf("l%d : Jp : : : IfEnd%d\n", line, tmpleft);
            line = line + 1;
            printf("IfFalse%d : Sk : : : \n", tmpleft);
            line = line + 1;
            P_Compile_C3A_eval(functions, ast->right->right);
            printf("IfEnd%d : Sk : : : \n", tmpleft);
            line = line + 1;
            break;
        case Wh:
            tmpjump = tmpjump + 1;
            tmpleft = tmpjump;
            printf("IfStart%d : Sk : : : \n", tmpleft);
            line = line + 1;
            P_Compile_C3A_eval(functions, ast->left);
            printf("l%d : Jz : _TMP%d : : IfEnd%d\n", line, tmpvar, tmpleft);
            line = line + 1;
            P_Compile_C3A_eval(functions, ast->right);
            printf("l%d : Jp : : : IfStart%d\n", line, tmpleft);
            line = line + 1;
            printf("IfEnd%d : Sk : : : \n", tmpleft);
            line = line + 1;
            break;
        case CallFUNC:
            line = line + 1;
            tmp4 = FuncList_search(functions, ((char*)ast->left->value));
            tmp6 = ast->right;
            for(int i = 0; i < tmp4->disclaimer->args->length; i++)
            {
                P_Compile_C3A_eval(functions, tmp6->right);
                printf("l%d : Param : _P%lu : _TMP%d :\n", line, tmp4->disclaimer->args->keys[i], tmpvar);
                line++;
                tmp6 = tmp6->left;
            }
            printf("l%d : Call : %s : %d :\n", line, (char*)ast->left->value, tmp4->disclaimer->args->length);
            line++;
            tmpvar++;
            printf("l%d : Af : _TMP%d : %s :\n", line, tmpvar,(char*)ast->left->value);
            line++;
            break;

    }
}