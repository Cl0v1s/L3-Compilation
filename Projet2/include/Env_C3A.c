#include "Env_C3A.h"

struct Env_C3A * Env_C3A_init()
{
    struct Env_C3A* env = malloc(sizeof(struct Env_C3A));
    env->keys = malloc(0);
    env->values = malloc(0);
    env->length = 0;
    return env;
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
    return Env_C3A_key_exists_hash(env, hash);
}
char Env_C3A_key_exists_hash(struct Env_C3A *env, unsigned long hash)
{

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
#ifdef DEBUG
    printf("Creating value %s : (%lu <- %d)\n", key, hash, value);
#endif
    Env_C3A_add_value_hash(env, hash, value);
}

void Env_C3A_add_value_hash(struct Env_C3A *env, unsigned long hash, int value)
{


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

void Env_C3A_set_value(struct Env_C3A *env, char* key, int value)
{
    unsigned long hash = Env_C3A_hash(key);
    Env_C3A_set_value_hash(env, hash, value);
#ifdef DEBUG
    printf("%s : (%lu <- %d)\n",key,  hash, value);
#endif
}

void Env_C3A_set_value_hash(struct Env_C3A *env, unsigned long hash, int value)
{
    if(Env_C3A_key_exists_hash(env, hash) == false)
    {
        Env_C3A_add_value_hash(env, hash, value);
        return;
    }

    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            env->values[i] = value;
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

void Env_C3A_free(struct Env_C3A* env)
{
    free(env->keys);
    free(env->values);
    free(env);
}

void Env_C3A_pop(struct Env_C3A* env, unsigned long* hash, int* value)
{
    *hash = env->keys[env->length-1];
    *value = env->values[env->length-1];

    unsigned long *keys = malloc((env->length-1)*sizeof(unsigned long));
    memcpy(keys, env->keys, (env->length-1)*sizeof(unsigned long));
    free(env->keys);
    env->keys = keys;

    int *values = malloc((env->length-1)*sizeof(int));
    memcpy(values, env->values, (env->length-1)*sizeof(int));
    free(env->values);
    env->values = values;

    env->length--;
}