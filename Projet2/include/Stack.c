#include "Stack.h"

struct Stack* Stack_init(){
  struct Stack* _stack = malloc(sizeof(struct Stack));
  _stack->size = 0;
  _stack->vars = malloc(0);
    return _stack;
}

int Stack_push(struct Stack* stack, int size){

    struct Variable** vars = malloc((stack->size+size)*sizeof(struct Variable*));
    memcpy(vars, stack->vars, stack->size*sizeof(struct Variable*));
    for(int i = stack->size; i != stack->size+size; i++)
    {
        vars[i] = 0;
    }
    free(stack->vars);
    stack->vars = vars;
    int index = stack->size;
    stack->size = stack->size + size;
    return index;
}

struct Variable* Stack_getVariable(struct Stack* stack, int index){
  if(index >= stack->size){
    printf("Index out of stack range.\n");
    exit(-1);
  }
  else {
    return stack->vars[index];
  }
}

void Stack_setVariable(struct Stack* stack, struct Variable* var, int index){
  if(index >= stack->size){
    printf("Index out stack range.\n");
    exit(-1);
  }
  else {
      stack->vars[index] = var;
  }
}

void Stack_remove(struct Stack* _stack, struct Variable* tab){
  //TODO : Recoller proprement un peu complexe, j'y reflechis. (supprimer le tableau, recoller le suivant, lui dire qu'il pointe maintenant sur le nouvel index..)
}


