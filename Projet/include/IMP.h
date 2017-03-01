#ifndef IMP_H
#define IMP_H

#include <string.h>
#include <stdio.h>

#include "Ast.h"
#include "Env.h"
#include "utils.h"
#include "../iimp.tab.h"

/**
* Wrapper permettant la création d'une feuille AST compatible IMP
* nodetype : type de noeud 
* value : valeur du noeud 
*/
struct Ast* Ast_IMP_init_leaf(int nodetype, void* value);

/**
* Parcours et execute un programme IMP
ast : programme à executer 
env : environnement dans lequel executer le programme
*/
int Ast_IMP_run(struct Ast* ast, Env *env);

#endif 