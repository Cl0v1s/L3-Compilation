#include "Env_C3A.h"

struct EnvC3A* EnvC3A_init()
{
    struct EnvC3A* env = malloc(sizeof(struct EnvC3A));
    env->keys = malloc(0);
    env->values = malloc(0);
    env->length = 0;
    return env;
}

struct EnvC3A* EnvC3A_copy(struct EnvC3A* source)
{
    struct EnvC3A* res = malloc(sizeof(struct EnvC3A));
    unsigned long *keys = malloc((source->length)*sizeof(unsigned long));
    memcpy(keys, source->keys, (source->length)*sizeof(unsigned long));
    res->keys = keys;

    int *values = malloc((source->length)*sizeof(int));
    memcpy(values, source->values, (source->length)*sizeof(int));
    res->values = values;

    res->length = source->length;
    return res;
}

void EnvC3A_print(struct EnvC3A *env)
{
    for(int i = 0; i < env->length; i++)
    {
        printf("(%lu:%d) ", env->keys[i], env->values[i]);
    }
    printf("\n");
}

char EnvC3A_key_exists(struct EnvC3A *env, char* key)
{
    unsigned long hash = EnvC3A_hash(key);

    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return true;
        }
    }
    return false;
}

int EnvC3A_get_value(struct EnvC3A *env, char* key)
{
    unsigned long hash = EnvC3A_hash(key);

    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return env->values[i];
        }
    }
    return -1;
}

void EnvC3A_add_value(struct EnvC3A *env, char* key, int value)
{

    unsigned long hash = EnvC3A_hash(key);

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

void EnvC3A_set_value(struct EnvC3A *env, char*key, int value)
{
    if(EnvC3A_key_exists(env, key) == false)
    {
        EnvC3A_add_value(env, key, value);
        return;
    }
    unsigned long hash = EnvC3A_hash(key);

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

unsigned long EnvC3A_hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void EnvC3A_pop(struct EnvC3A* env, unsigned long* hash, int* value)
{
    if(hash != 0)
        *hash = env->keys[env->length-1];
    if(value != 0)
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