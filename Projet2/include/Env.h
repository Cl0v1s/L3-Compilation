#ifndef DICT_HEADER
#define DICT_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Variable.h"

/**
* Environnement de variables (Table de Hash)
L_vart
**/
struct Env
{
    unsigned long *keys;
    struct Variable** values;
    int length;
};

unsigned long Env_hash(char *str);

/**
* Initialise un nouvel Environnement
* env : Environnement à initialiser
*/
struct Env* Env_init();
/**
* Affiche un environnement 
* env : environnement à afficher
* stack : tas rattaché à l'environnement à afficher
**/
void Env_print(struct Env* env, struct Stack* stack);
/**
* Test si la clef key existe 
* env : environnement à tester 
* key : clef dont il est nécessaire de tester l'existence
*/
char Env_key_exists(struct Env* env, char* key);

char Env_hash_exists(struct Env* env, unsigned long hash);

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

void Env_set_value_index(struct Env* env, int index, struct Variable* value);

struct Env* Env_concat(struct Env* env1, struct Env* env2);

unsigned long Env_get_key_index(struct Env* env, int index);

struct Variable* Env_get_value_index(struct Env* env, int index);

void Env_free(struct Env* env);

void Env_add_value_hash(struct Env* env, unsigned long hash, struct Variable* value);

int Env_checkEnvCollision(struct Env* env1, struct Env* env2);

#endif