//
// Created by nazruden on 4/2/17.
//

#include "Variable.h"
#include "Env.h"
#include "Stack.h"

/*int main()
{
    *//** VARS **//*
    // Stack
    struct Stack* stack = Stack_init();
    // Array of int type
    struct Type* intArray = Type_init(ARRAY, Type_INT);
    // Init array
    struct Variable* array = Variable_arrayInit(intArray, stack, 10);

    struct Variable* var = Variable_init(INT);
    Variable_set(var, 5);
    Variable_arraySet(array, stack, var, array->value);

//
//
//    Variable_set(var, 10);
//        struct Variable* var2 = Variable_init(INT);
//    Variable_set(var2, 100);
//
//        struct Variable* var3 = Variable_init(INT);
//    Variable_set(var3, 1000);
//
//
//    struct Env env;
//    Env_init(&env);
//    Env_add_value(&env, "test1",var);
//    Env_add_value(&env, "test2",var2);
//    Env_add_value(&env, "test3",var3);
//
//    struct Variable* res = Env_get_value(&env, "test1");
//    Variable_print(res);
//    res = Env_get_value(&env, "test2");
//    Variable_print(res);
//    res = Env_get_value(&env, "test3");
//    Variable_print(res);

}*/

