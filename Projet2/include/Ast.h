#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>

#include "Env.h"
//#include "utils.h"
//#include "../iimp.tab.h"

/**
* Représente un arbre valué 
**/
struct Ast{
    int nodetype;
    void* value;
    struct Ast* left;
    struct Ast* right;
};

/**
* Initialise un arbre (ou un noeud d'un arbre de taille supérieure)
* nodetype : type de noeud, 
* ope : opération du noeud 
* left : fils gauche du noeud 
* right : fils droit du noeud 
*/
struct Ast* Ast_init(int nodetype,int ope, struct Ast* left,struct Ast *right);

/**
* Initialise une feuille d'un arbre
* nodetype : type de noeud 
* value : valeur de la feuille 
*/
struct Ast* Ast_init_leaf(int nodetype, void* value);


#endif 