#include "Env_C3A.h"

void Env_C3A_init(struct Env_C3A *env)
{
    env->keys = malloc(0);
    env->values = malloc(0);
    env->length = 0;
}

void Env_C3A_print(struct Env_C3A *env)
{
    for(int i = 0; i < env->length; i++)
    {
        printf("(%lu:%d) ", env->keys[i], env->values[i]);
    } 
    printf("\n"); 
}

char Env_C3A_key_exists(struct Env_C3A *env, char* key)
{
    unsigned long hash = Env_C3A_hash(key);
    
    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return true;
        }
    }
    return false;
}

int Env_C3A_get_value(struct Env_C3A *env, char* key)
{
    unsigned long hash = Env_C3A_hash(key);
    
    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return env->values[i];
        }
    }   
    return -1;
}

void Env_C3A_add_value(struct Env_C3A *env, char* key, int value)
{

    unsigned long hash = Env_C3A_hash(key);

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
    #ifdef DEBUG
        printf("Creating value %s : (%lu <- %d)\n", key, hash, value);
    #endif
}

void Env_C3A_set_value(struct Env_C3A *env, char*key, int value)
{
    if(Env_C3A_key_exists(env, key) == false)
    {
        Env_C3A_add_value(env, key, value);
        return;
    }
    unsigned long hash = Env_C3A_hash(key);

    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            env->values[i] = value;
            #ifdef DEBUG
                printf("%s : (%lu <- %d)\n",key,  hash, value);
            #endif            
            return;
        }
    }
}

unsigned long Env_C3A_hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}