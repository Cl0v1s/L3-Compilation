#ifndef QUADS_H
#define QUADS_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Env_C3A.h"

#include "Stack.h"

#define false 0
#define true 1


struct Value{
    char type;
    void *value;
};

struct Quad{
    char *address;
    int  operation;
    struct Value* arg1;
    struct Value* arg2;
    char* destination;
    struct Quad *next;
};

struct QuadList{
    struct Quad* start;
    struct Quad* end;
};

/**
* Créer une nouvelle valeur 
* type : type de la valeur à créer 
* value: valeur
*/
struct Value* Value_create(char type, void* value);

/**
* Récupère l'entier associé à la valeur 
* value : valeur dans laquel chercher 
* env :  environnement 
*/
int Value_get(struct Value* value, struct EnvC3A* env, struct Stack* stack, int* pos, int* adr, int* size, int index);

void Value_delete(struct Value* value);

/**
* Créer une nouvelle liste de quads 
* quad : quad à ajouter dans la liste
*/
struct QuadList* QuadList_create(struct Quad* quad);

void QuadList_delete(struct QuadList* list);

void QuadList_deleteAll(struct QuadList* list);

/**
* Concatène deux listes de quads 
* first : une liste de quads 
* second : une liste de quads 
**/
struct QuadList* QuadList_concat(struct QuadList* first, struct QuadList* second);

/**
* Recherche un quad étiqueté dans une liste de quads 
* list : liste de quads dans laquelle chercher 
* address : etiquette du quad à rechercher
**/
struct Quad* QuadList_search(struct QuadList* list, char* address);

/**
* Créer un nouveau quad 
* address :  etiquette du quad 
* ope : opération associée au quad
* arg1 : valeur premier argument 
* arg2 : valeur deuxième argument 
* destination : destination
*/
struct Quad* Quad_create(char* address, int ope, struct Value* arg1, struct Value* arg2, char* destination);

/**
Teste si un quad possède l'étiquette donnée 
* quad: Quad à tester 
* address : etiquette à tester 
*/
int Quad_hasAddress(struct Quad* quad, char* address);

void Quad_setAddress(struct Quad* quad, char* value);

void Quad_delete(struct Quad* quad);





#endif