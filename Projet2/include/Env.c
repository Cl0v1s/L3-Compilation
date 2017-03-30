#include "Env.h"

struct Env* Env_init()
{
    struct Env* env = malloc(sizeof(struct Env));
    env->keys = malloc(0);
    int size = ARRAY;
    env->values = Variable_init(size);
    env->length = 0;
    return env;
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

unsigned long Env*_get_key_index(struct Env* env, int index)
{
    if(index >= env->length)
        return 0;
    return env->keys[i];
}

struct Variable* Env_get_value_index(struct Env* env, int index)
{
    if(index >= env->length)
        return 0;
    return Variable_arrayGet(env->values, i);
}

void Env_add_value_hash(struct Env* env, unsigned long hash, struct Variable* value)
{
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

struct Env* Env_concat(struct Env* env1, struct Env* env2)
{
    struct Env* res = Env_init();
    for(int i = 0; i != env1->length; i++)
    {
        Env_
    }
}