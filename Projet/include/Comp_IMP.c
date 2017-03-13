#include "Comp_IMP.h"

int line = 0;
int tmpvar = 0;

void IMP_Compile_C3A(struct Ast* ast)
{
    if(ast->nodetype == 'I')
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
            IMP_Compile_C3A(ast->left);
            tmpleft = tmpvar;
            IMP_Compile_C3A(ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Pl : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
        break;
        case Mo:
            IMP_Compile_C3A(ast->left);
            tmpleft = tmpvar;
            IMP_Compile_C3A(ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mo : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
        break;
        case Mu:
            IMP_Compile_C3A(ast->left);
            tmpleft = tmpvar;
            IMP_Compile_C3A(ast->right);
            tmpright = tmpvar;
            tmpvar = tmpvar + 1;
            printf("l%d : Mu : _TMP%d : _TMP%d : _TMP%d\n", line, tmpleft, tmpright, tmpvar);
            line = line + 1;
        break;
        case Af:
            IMP_Compile_C3A(ast->right);
            printf("l%d : Af : %s : _TMP%d :\n", line, (char*)ast->left->value, tmpvar);
            line = line + 1;
        break;
        case Sk:
            printf("l%d : Sk :  :  :\n", line);
            line = line + 1;
        break;
        case Se:
            IMP_Compile_C3A(ast->left);
            IMP_Compile_C3A(ast->right);
        break;
    }
}

