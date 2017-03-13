#ifndef DICT_HEADER
#define DICT_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/**
* Environnement de variables (Table de Hash)
**/
typedef struct
{
    unsigned long *keys;
    int *values;
    int length;
}Env;

unsigned long Env_hash(char *str);

/**
* Initialise un nouvel Environnement
* env : Environnement à initialiser
*/
void Env_init(Env *env);
/**
* Affiche un environnement 
* env : environnement à afficher
**/
void Env_print(Env *env);
/**
* Test si la clef key existe 
* env : environnement à tester 
* key : clef dont il est nécessaire de tester l'existence
*/
char Env_key_exists(Env *env, char* key);

/**
* Ajoute une nouvelle entrée dans l'environnement
* env : environnement dans lequel ajouter 
* key : clef de la valeur à ajouter 
* value : valeur à ajouter 
*/
void Env_add_value(Env *env, char* key, int value);

/**
* Récupère une valeur à partir de sa clef 
* env : environnement dans lequel récupérer 
* key : clef de la valeur à récupérer
*/
int Env_get_value(Env *env, char* key);

/**
* Change/ajoute une valeur 
* env: environnement à modifier 
* key : clef de la valeur 
* value: valeur 
*/
void Env_set_value(Env *env, char* key, int value);

#endif