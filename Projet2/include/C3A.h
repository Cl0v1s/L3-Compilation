#ifndef C3A_H
#define C3A_H

#include "Env_C3A.h"
#include "Quads.h"
#include "./../c3ainterpret.tab.h"

#define false 0
#define true 1


void C3A_replace(struct EnvC3A* env, struct Stack* stack,  char* key, int value);

/**
* Lance le parcours et l'execution d'un programme C3A
* list: programme C3A
* env : Environnement de variables 
*/
void C3A_run(struct QuadList* list, struct EnvC3A* env);

/**
* Modifie env en fonction de la commande quad
* quad : Commande C3A
* env : environnement sur lequel agit la commande 
* list : totalité du programme C3A
*/
struct Quad* C3A_eval(struct Quad* quad, struct EnvC3A* env, struct QuadList* list, struct Stack* stack);



#endif