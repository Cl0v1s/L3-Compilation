#ifndef C3A_H
#define C3A_H

#include "utils.h"
#include "Env.h"
#include "Quads.h"
#include "utils.h"
#include "./../c3a.tab.h"


/**
* Lance le parcours et l'execution d'un programme C3A
* list: programme C3A
* env : Environnement de variables 
*/
void C3A_run(struct QuadList* list, Env* env);

/**
* Modifie env en fonction de la commande quad
* quad : Commande C3A
* env : environnement sur lequel agit la commande 
* list : totalité du programme C3A
*/
struct Quad* C3A_eval(struct Quad* quad, Env* env, struct QuadList* list);



#endif