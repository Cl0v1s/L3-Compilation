#include "Variable.h"
#include "Env.h"

/*
int main()
{
    struct Variable* var = Variable_init(INT);
    Variable_set(var, 10);
        struct Variable* var2 = Variable_init(INT);
    Variable_set(var2, 100);

        struct Variable* var3 = Variable_init(INT);
    Variable_set(var3, 1000);


    struct Env env;
    Env_init(&env);
    Env_add_value(&env, "test1",var);
    Env_add_value(&env, "test2",var2);
    Env_add_value(&env, "test3",var3);

    struct Variable* res = Env_get_value(&env, "test1");
    Variable_print(res);
    res = Env_get_value(&env, "test2");
    Variable_print(res);
    res = Env_get_value(&env, "test3");
    Variable_print(res);

}*/
