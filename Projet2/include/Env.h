#ifndef DICT_HEADER
#define DICT_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Variable.h"

/**
* Environnement de variables (Table de Hash)
**/
struct Env
{
    unsigned long *keys;
    struct Variable* values;
    int length;
};

unsigned long Env_hash(char *str);

/**
* Initialise un nouvel Environnement
* env : Environnement à initialiser
*/
void Env_init(struct Env* env);
/**
* Affiche un environnement 
* env : environnement à afficher
**/
void Env_print(struct Env* env);
/**
* Test si la clef key existe 
* env : environnement à tester 
* key : clef dont il est nécessaire de tester l'existence
*/
char Env_key_exists(struct Env* env, char* key);

/**
* Ajoute une nouvelle entrée dans l'environnement
* env : environnement dans lequel ajouter 
* key : clef de la valeur à ajouter 
* value : valeur à ajouter 
*/
void Env_add_value(struct Env* env, char* key, struct Variable* value);

/**
* Récupère une valeur à partir de sa clef 
* env : environnement dans lequel récupérer 
* key : clef de la valeur à récupérer
*/
struct Variable* Env_get_value(struct Env* env, char* key);

/**
* Change/ajoute une valeur 
* env: environnement à modifier 
* key : clef de la valeur 
* value: valeur 
*/
void Env_set_value(struct Env* env, char* key, struct Variable* value);

#endif