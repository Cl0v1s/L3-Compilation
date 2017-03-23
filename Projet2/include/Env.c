#include "Env.h"

void Env_init(struct Env* env)
{
    env->keys = malloc(0);
    int size = ARRAY(1);
    env->values = Variable_init(size);
    env->length = 0;
}

void Env_print(struct Env* env)
{
    for(int i = 0; i < env->length; i++)
    {
        printf("(%lu:%p) ", env->keys[i], Variable_arrayGet(env->values, i));
    } 
    printf("\n"); 
} 

char Env_key_exists(struct Env* env, char* key)
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

struct Variable* Env_get_value(struct Env* env, char* key)
{
    unsigned long hash = Env_hash(key);
    
    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return Variable_arrayGet(env->values, i);
        }
    }   
    return 0;
}

void Env_add_value(struct Env* env, char* key, struct Variable* value)
{

    unsigned long hash = Env_hash(key);

    unsigned long *keys = malloc((env->length+1)*sizeof(unsigned long));
    memcpy(keys, env->keys, (env->length)*sizeof(unsigned long));
    keys[env->length] = hash;
    free(env->keys);
    env->keys = keys;

    Variable_arraySet(env->values, env->length, value);

    env->length++;
    #ifdef DEBUG
        printf("Creating value %s : (%lu <- %p)\n", key, hash, value);
    #endif
}

void Env_set_value(struct Env* env, char*key, struct Variable* value)
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
            Variable_arraySet(env->values, i, value);
            #ifdef DEBUG
                printf("%s : (%lu <- %p)\n",key,  hash, value);
            #endif            
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