#include "Verification.h"

void Verif_call(int id){
    if(id > 0 && id < 5){
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
            case 4 :
                Verif_Code4();
                break;
        }
    }
    else{
        printf("VERIFICATION : Wrong code id. ( %i )\n", id);
    }
}

void Verif_Code1(){
    /** Code **/
    // var X1 : array of integer,
    // var X2 : array of array of integer
    //
    // X1 := new array of integer ;
    // X2 := new array of array of integer ;
    // X1[0] := 0;
    // X1[1] := 1;
    //
}

void Verif_Code2(){

}

void Verif_Code3(){

}

void Verif_Code4(){

}
