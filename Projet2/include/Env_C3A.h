#ifndef ENVC3A_HEADER
#define ENVC3A_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define false 0
#define true 1
/**
* EnvC3Aironnement de variables (Table de Hash)
**/
struct EnvC3A
{
    unsigned long *keys;
    int *values;
    int length;
};

unsigned long EnvC3A_hash(char *str);

/**
* Initialise un nouvel EnvC3Aironnement
* env : EnvC3Aironnement à initialiser
*/
struct EnvC3A* EnvC3A_init();
/**
* Affiche un environnement 
* env : environnement à afficher
**/
void EnvC3A_print(struct EnvC3A *env);
/**
* Test si la clef key existe 
* env : environnement à tester 
* key : clef dont il est nécessaire de tester l'existence
*/
char EnvC3A_key_exists(struct EnvC3A *env, char* key);

/**
* Ajoute une nouvelle entrée dans l'environnement
* env : environnement dans lequel ajouter 
* key : clef de la valeur à ajouter 
* value : valeur à ajouter 
*/
void EnvC3A_add_value(struct EnvC3A *env, char* key, int value);

/**
* Récupère une valeur à partir de sa clef 
* env : environnement dans lequel récupérer 
* key : clef de la valeur à récupérer
*/
int EnvC3A_get_value(struct EnvC3A *env, char* key);

/**
* Change/ajoute une valeur 
* env: environnement à modifier 
* key : clef de la valeur 
* value: valeur 
*/
void EnvC3A_set_value(struct EnvC3A *env, char* key, int value);

#endif