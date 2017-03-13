#include "Env.h"

void Env_init(Env *env)
{
    env->keys = malloc(0);
    env->values = malloc(0);
    env->length = 0;
}

void Env_print(Env *env)
{
    for(int i = 0; i < env->length; i++)
    {
        printf("(%lu:%d) ", env->keys[i], env->values[i]);
    } 
    printf("\n"); 
}

char Env_key_exists(Env *env, char* key)
{
    unsigned long hash = Env_hash(key);
    
    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return true;
        }
    }
    return false;
}

int Env_get_value(Env *env, char* key)
{
    unsigned long hash = Env_hash(key);
    
    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return env->values[i];
        }
    }   
    return -1;
}

void Env_add_value(Env *env, char* key, int value)
{

    unsigned long hash = Env_hash(key);

    unsigned long *keys = malloc((env->length+1)*sizeof(unsigned long));
    memcpy(keys, env->keys, (env->length)*sizeof(unsigned long));
    keys[env->length] = hash;
    free(env->keys);
    env->keys = keys;

    int *values = malloc((env->length+1)*sizeof(int));
    memcpy(values, env->values, (env->length)*sizeof(int));
    values[env->length] = value;
    free(env->values);
    env->values = values;

    env->length++;
}

void Env_set_value(Env *env, char*key, int value)
{
    if(Env_key_exists(env, key) == false)
    {
        Env_add_value(env, key, value);
        return;
    }
    unsigned long hash = Env_hash(key);

    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            env->values[i] = value;
            return;
        }
    }
}

unsigned long Env_hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}