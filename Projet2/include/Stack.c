#include "Stack.h"

struct Stack* Stack_init(){
  struct Stack* _stack = malloc(sizeof(struct Stack));
  _stack->size = 0;
  _stack->vars = malloc(_stack->size * sizeof(struct Variable*));
}

void Stack_push(struct Stack* _stack, struct Variable* tab){
  int size = _stack->size + tab->size;
  struct Variable** newVars = malloc(size*sizeof(struct Variable*));
  memcpy(newVars, _stack->vars, _stack->size*sizeof(struct Variable*));
  newVars[_stack->size] = tab;
  free(_stack->vars);
  _stack->vars = newVars;
  _stack->size = size;
}

void Stack_getVariable(){

}
