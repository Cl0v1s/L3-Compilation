//
// Created by quentin on 05/04/17.
//

#include "Comp_Pascal.h"

int line = 0;
int tmpvar = 0;
int tmpjump = 0;

void P_Compile_C3A(struct FuncList* functions, struct Ast* ast)
{
    if(ast == 0)
        return;
    printf("COMPILING %p ", ast);
    Ast_print(ast);
    if(ast->nodetype == 'I' || ast->nodetype == 'B')
    {
        tmpvar = tmpvar + 1;
        printf("l%d : Afc : %d : : _TMP%d\n", line, *(int*)ast->value, tmpvar);
        line = line + 1;
        return;
    }
    if(ast->nodetype == 'V')
    {
        tmpvar = tmpvar + 1;
        printf("l%d : Af : _TMP%d : %s :\n", line, tmpvar, (char*)ast->value);
        line = line + 1;
        return;
    }

    // On arrive ici si le noeud n'est pas une feuille
    int ope = *(int*)ast->value;
    int tmpleft;
    int tmpright;
    switch(ope)
    {
        case Pl:
            P_Compile_C3A(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Pl : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Mo:
            P_Compile_C3A(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mo : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Mu:
            P_Compile_C3A(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mu : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case And:
            P_Compile_C3A(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : And : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Or:
            P_Compile_C3A(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Or : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Lt:
            P_Compile_C3A(functions, ast->left);
            tmpleft = tmpvar;
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : And : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
            break;
        case Not:
            P_Compile_C3A(functions, ast->left);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Not : _TMP%d :  : _TMP%d\n", line, tmpright,  tmpvar);
            line = line + 1;
            break;
        case GetARR:
            P_Compile_C3A(functions, ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Ind : %s : _TMP%d : _TMP%d\n", line, (char*)ast->left->value, tmpright, tmpvar);
            line = line + 1;
            break;
        case Af:
            P_Compile_C3A(functions, ast->right);
            if(*(int*)ast->left->value == GetARR)
            {
                tmpright = tmpvar;
                P_Compile_C3A(functions, ast->left->right);
                printf("l%d : AfInd : %s : _TMP%d : _TMP%d\n", line, (char*)ast->left->left->value, tmpvar, tmpright);
            }
            else
                printf("l%d : Af : %s : _TMP%d :\n", line, (char*)ast->left->value, tmpvar);
            line = line + 1;
            break;
        case Sk:
            printf("l%d : Sk :  :  :\n", line);
            line = line + 1;
            break;
        case Se:
            P_Compile_C3A(functions,ast->left);
            P_Compile_C3A(functions, ast->right);
            break;
        case If:
            tmpjump = tmpjump + 1;
            tmpleft = tmpjump;
            P_Compile_C3A(functions, ast->left);
            printf("l%d : Jz : _TMP%d : : IfFalse%d\n", line, tmpvar, tmpleft);
            line = line + 1;
            P_Compile_C3A(functions, ast->right->left);
            printf("l%d : Jp : : : IfEnd%d\n", line, tmpleft);
            line = line + 1;
            printf("IfFalse%d : Sk : : : \n", tmpleft);
            line = line + 1;
            P_Compile_C3A(functions, ast->right->right);
            printf("IfEnd%d : Sk : : : \n", tmpleft);
            line = line + 1;
            break;
        case Wh:
            tmpjump = tmpjump + 1;
            tmpleft = tmpjump;
            printf("IfStart%d : Sk : : : \n", tmpleft);
            line = line + 1;
            P_Compile_C3A(functions, ast->left);
            printf("l%d : Jz : _TMP%d : : IfEnd%d\n", line, tmpvar, tmpleft);
            line = line + 1;
            P_Compile_C3A(functions, ast->right);
            printf("l%d : Jp : : : IfStart%d\n", line, tmpleft);
            line = line + 1;
            printf("IfEnd%d : Sk : : : \n", tmpleft);
            line = line + 1;
            break;
    }
}

