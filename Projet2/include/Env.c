#include "Env.h"

struct Env* Env_init()
{
    struct Env* env = malloc(sizeof(struct Env));
    env->keys = malloc(0);
    int size = ARRAY;
    env->values = malloc(0);
    env->length = 0;
    return env;
}

void Env_print(struct Env* env, struct Stack* stack)
{
    for(int i = 0; i < env->length; i++)
    {
        // TODO : appeler Variable_get ou Variable_arrayGet correctement
//        printf("(%lu:%p) ", env->keys[i], Variable_arrayGet(env->values, stack, i));
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

char Env_hash_exists(struct Env* env, unsigned long hash)
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

struct Variable* Env_get_value(struct Env* env, char* key)
{
    unsigned long hash = Env_hash(key);
    
    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            return env->values[i];
        }
    }   
    return 0;
}

unsigned long Env_get_key_index(struct Env* env, int index)
{
    if(index >= env->length)
        return 0;
    return env->keys[index];
}

struct Variable* Env_get_value_index(struct Env* env, int index)
{
    if(index >= env->length)
        return 0;
    return env->values[index];
}

void Env_add_value_hash(struct Env* env, unsigned long hash, struct Variable* value)
{
    if(Env_hash_exists(env, hash) == true)
    {
        printf("Cant add hash, already exists.\n");
        exit(-1);
    }


    unsigned long *keys = malloc((env->length+1)*sizeof(unsigned long));
    memcpy(keys, env->keys, (env->length)*sizeof(unsigned long));
    keys[env->length] = hash;
    free(env->keys);
    env->keys = keys;

    struct Variable** values = malloc((env->length+1)*sizeof(struct Variable*));
    memcpy(values, env->values, (env->length)*sizeof(struct Variable*));
    values[env->length] = value;
    free(env->values);
    env->values = values;

    env->length++;
    #ifdef DEBUG
    // TODO : Je sais pas ce par quoi key doit être remplacé ici (j'ai pensé à keys[env->length] pour la clé rajouté
    //          présentement mais ça ferait redondance avec hash ? m'enfin à toi de voir ! :)
    //        printf("Creating value %s : (%lu <- %p)\n", key, hash, value);
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

    struct Variable** values = malloc((env->length+1)*sizeof(struct Variable*));
    memcpy(values, env->values, (env->length)*sizeof(struct Variable*));
    values[env->length] = value;
    free(env->values);
    env->values = values;

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
        value->refs = value->refs + 1;
        return;
    }
    unsigned long hash = Env_hash(key);

    for(int i = 0; i < env->length; i++)
    {
        if(env->keys[i] == hash)
        {
            env->values[i] = value;
            value->refs = value->refs + 1;
            #ifdef DEBUG
                printf("%s : (%lu <- %p)\n",key,  hash, value);
            #endif            
            return;
        }
    }
}

void Env_set_value_index(struct Env* env, int index, struct Variable* value)
{
    if(index >= env->length)
        return;
    value->refs = value->refs + 1;
    env->values[index] = value;
}

unsigned long Env_hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void Env_free(struct Env* env)
{
    free(env->keys);
    free(env->values);
    free(env);
}

struct Env* Env_concat(struct Env* env1, struct Env* env2)
{
    struct Env* res = Env_init();
    for(int i = 0; i != env1->length; i++)
    {
        unsigned long key = Env_get_key_index(env1, i);
        struct Variable* value = Env_get_value_index(env1, i);
        Env_add_value_hash(res, key, value);
    }
    if(env2 == 0)
        return res;
    for(int i = 0; i != env2->length; i++)
    {
        unsigned long key = Env_get_key_index(env2, i);
        struct Variable* value = Env_get_value_index(env2, i);
        Env_add_value_hash(res, key, value);
    }
    return res;
}

int Env_checkEnvCollision(struct Env* env1, struct Env* env2){
    int ok = true;
    int i = 0;
    int j = 0;
    while(ok && i < env1->length){
        while(ok && j < env2->length) {
            if (env1->keys[i] == env2->keys[j]) {
                ok = false;
            }
            j++;
        }
        i++;
    }
    return ok;
}