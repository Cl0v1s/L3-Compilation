#ifndef Comp_C3A_H
#define Comp_C3A_H

#include "utils.h"
#include "Env.h"
#include "Quads.h"
#include "./../comp_c3a.tab.h"

/**
* Compte le nombre d'instruction en Y86 demandée par un programme en C3A
* list: programme C3A
**/
int Comp_C3A_countInstructions(struct QuadList* list);

/**
* Prepare les emplacement dans la mémoire Y86 des différentes variables C3A
* list: programme C3A
* memoryend: premiere case non occupée par la mémire des variables
**/
Env* Comp_C3A_declareVariables(struct QuadList* list, int * memoryend);

/**
* Compile un programme C3A en Y86
* list: programme C3A
**/
void C3A_Compile_Y86(struct QuadList* list);

/**
* Traduit une commande C3A en instruction Y86
* quad: instruction C3A
* memorystart: emplacement mémoire à laquelle commence les variables
* variablesOffset: hashmap associant nom de variable a une position dans la zone des variables mémoire
**/
void Comp_C3A_translate(struct Quad* quad, int memorystart, Env* variablesOffset);

#endif 