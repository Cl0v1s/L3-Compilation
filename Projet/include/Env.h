#ifndef DICT_HEADER
#define DICT_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

typedef struct
{
    char* *keys;
    int *values;
    int length;
}Env;

void Env_init(Env *env);
void Env_print(Env *env);
char Env_key_exists(Env *env, char* key);
void Env_add_value(Env *env, char* key, int value);
int Env_get_value(Env *env, char* key);
void Env_set_value(Env *env, char* key, int value);

#endif