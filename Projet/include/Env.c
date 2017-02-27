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
        printf("(%s:%d) ", env->keys[i], env->values[i]);
    } 
    printf("\n"); 
}

char Env_key_exists(Env *env, char* key)
{
    for(int i = 0; i < env->length; i++)
    {
        if(strcmp(env->keys[i], key) == 0)
        {
            return true;
        }
    }
    return false;
}

int Env_get_value(Env *env, char* key)
{
    for(int i = 0; i < env->length; i++)
    {
        if(strcmp(env->keys[i], key) == 0)
        {
            return env->values[i];
        }
    }   
    return -1;
}

void Env_add_value(Env *env, char* key, int value)
{
    int strlength = 0;
    for(int i = 0; i < env->length; i++)
    {
        strlength += strlen(env->keys[i])+1;
    }

    char** keys = malloc(strlength+strlen(key)+1);
    memcpy(keys, env->keys, strlength);
    env->keys[env->length] = malloc(strlen(key)+1);
    strcpy(env->keys[env->length], key);



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

    for(int i = 0; i < env->length; i++)
    {
        if(strcmp(env->keys[i], key) == 0)
        {
            env->values[i] = value;
            return;
        }
    }
}