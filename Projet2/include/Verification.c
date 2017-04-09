#include "Verification.h"

void Verif_call(int id, struct Env* env, struct Stack* stack){
    if(id > 0 && id < 4){
        switch(id){
            case 1 :
                Verif_Code1();
                break;
            case 2 :
                Verif_Code2();
                break;
            case 3 :
                Verif_Code3();
                break;
        }
    }
    else{
        printf("VERIFICATION : Wrong code id. ( %i )\n", id);
    }
}

void Verif_Code1(struct Env* env, struct Stack* stack){
    /** Code **/
//    var X1 : array of integer,
//    var X2 : array of array of integer,
//    var I : integer,
//    var S1 : integer,
//    var S2  integer
//
//    X1 := new array of integer[5];
//    X2 := new array of array of integer[5];
//    I := 0;
//    S1 := 5;
//    S2 := 5;
//    while I < S1 do
//        X1[I] := I;
//    I := I + 1
//
//    I := 0;
//
//    while I < S2 do
//        X2[I][I] = X1[I];
//    I := I + 1;

    /** Vérification **/
    // Verif X1
    char* X = "X1";
    if(Env_key_exists(env, X)){
        // Testing X1[0] to X1[3]
        for(int i = 0; i < 5; i ++) {
            struct Variable *var = Env_get_value(env, X);
            int val = Variable_arrayGet(var, stack, i);
            if (val != i) {
                printf("VERIFICATION : For %s [%i]Values are not the ones expected. Expected [ %i ] but had [ %i ].\n",
                       X, i, i, val);
            }
        }
    }
    else {
        printf("VERIFICATION : Undefined : %s not found in environment.\n", X);
    }
    // Verif X2
    X = "X2";
    if(Env_key_exists(env, X)){
        for(int i = 0; i < 5; i ++){
            struct Variable *var = Env_get_value(env, X);
            // On récupère dans le premier tableau l'adresse du sous tableau avec un premier indice
            int vari = Variable_arrayGet(var, stack, i);

            // On récupère dans le deuxième tableau
            int val = Stack_getValueByAdr(stack, vari, i);
            if(val == i){
                printf("Ok.\n");
            }
        }
    }
}

void Verif_Code2(struct Env* env, struct Stack* stack){
    /** Code **/
//    var X1 : array of array of array of integer,
//    var X2 : array of array of array of boolean
//
//    X1 := new array of array of array of integer[3];
//    X2 := new array of array of array of boolean[3];
//    X1[0][0][0] = 0;
//    X1[0][0][1] = 1;
//    X1[0][0][2] = 2;
//    X1[0][1][0] = 3;
//    X1[0][1][1] = 4;
//    X1[0][1][2] = 5;
//    X1[1][1][0] = 6;
//    X1[1][1][1] = 7;
//    X1[1][1][2] = 8;
//    X2[0][0][0] = true;
//    X2[0][0][1] = true;
//    X2[0][0][2] = true;
//    X2[0][1][0] = false;
//    X2[0][1][1] = false;
//    X2[0][1][2] = false;
//    X2[1][1][0] = true;
//    X2[1][1][1] = true;
//    X2[1][1][2] = true;

    // Verif X1
    char* X = "X1";
    if(Env_key_exists(env, X)){
        for(int i = 0; i < 3; i++){

        }
    }

    X = "X2";
    if(Env_key_exists(env, X)){
        for(int i = 0; i < 3; i++){

        }
    }

}

void Verif_Code3(struct Env* env, struct Stack* stack){

}
