#include "Stack.h"

struct Stack* Stack_init(){
  struct Stack* _stack = malloc(sizeof(struct Stack));
  _stack->size = 0;
  _stack->vars = malloc(_stack->size * sizeof(struct Variable*));
}

int Stack_push(struct Stack* _stack, struct Variable* tab){
  int size = _stack->size + tab->size;
  int returnedIndex = _stack->size;
  struct Variable** newVars = malloc(size*sizeof(struct Variable*));
  memcpy(newVars, _stack->vars, _stack->size*sizeof(struct Variable*));
  newVars[_stack->size] = tab;
  free(_stack->vars);
  _stack->vars = newVars;
  _stack->size = size;
  return returnedIndex;
}

struct Variable* Stack_getVariable(struct Stack* _stack, int index){
  if(index >= _stack->size){
    printf("Index out of stack range.\n");
    exit(-1);
  }
  else {
    return _stack->vars[index];
  }
}

void Stack_setVariable(struct Stack* _stack, struct Variable* var, int index){
  if(index >= _stack->size){
    printf("Index out stack range.\n");
    exit(-1);
  }
  else {
    _stack->vars[index] = var;
  }
}

void Stack_remove(struct Stack* _stack, struct Variable* tab){
  //TODO : Recoller proprement un peu complexe, j'y reflechis. (supprimer le tableau, recoller le suivant, lui dire qu'il pointe maintenant sur le nouvel index..)
}


