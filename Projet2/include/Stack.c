#include "Stack.h"
#include "Variable.h"

struct Stack* Stack_init(){
  struct Stack* _stack = malloc(sizeof(struct Stack));
  _stack->size = 0;
  _stack->vars = malloc(0);
    return _stack;
}

int Stack_push(struct Stack* stack, int size) {

    struct Variable **vars = malloc((stack->size + size) * sizeof(struct Variable *));
    memcpy(vars, stack->vars, stack->size * sizeof(struct Variable *));
    for (int i = stack->size; i != stack->size + size; i++) {
        vars[i] = 0;
    }
    free(stack->vars);
    stack->vars = vars;
    int index = stack->size;
    stack->size = stack->size + size;

#ifdef DEBUG
    printf("Pushed to stack at Ind %i for size %i. StackSize : %i\n", index, size, stack->size);
#endif

    return index;
}

int Stack_isIndexValid(struct Stack* _stack, int index){
    if(index >= _stack->size){
        printf("Index ouf of stack.\n");
        exit(-1);
    }
    else {
        return 1;
    }
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

// TODO : essayer de modifier les appels à cette fonction. Je sais pas comment redéfinir
//      les index de début de tableau de ceux impactés si l'on fait un shift de la fin pour
//      venir se positionner sur la zone supprimée, dans le contexte de cette déclaration
void Stack_remove(struct Stack* _stack, int index, int size){
    if(Stack_isIndexValid(_stack, index)){
        for(int i = index; i < index + size; i++){
            free(_stack->vars[i]);
            _stack->vars[i] = NULL;
        }
    }
}

void Stack_removeArray(struct Stack* _stack, struct Variable* start){
  //TODO : Recoller proprement dans un tel contexte où on ne connaît que start n'est pas possible si start n'est pas également le dernier du tas
    // Plage de suppression invalide
    if(*(int*)start->value >= _stack->size || *(int*)(start->value + start->size) >= _stack->size){
        printf("Suppression range invalid. [%i:%i]>[%i]\n", *(int *)start->value, *(int *)start->value+start->size, _stack->size);
    }
    struct Variable* startVar = _stack->vars[*(int*)start->value];

    // Remove one
}

int Stack_rangeValid(struct Stack* _stack, struct Variable* var){
    if(*(int*)var->value < _stack->size && *(int*)var->value + var->size < _stack->size){
        return 1;
    }
    else {
        return 0;
    }
}

// TODO : Sans doute la seule utilisation réellement propre puisque l'on est sensé free en (attention abus de langage) dépilant le contexte ? J'imagine
void Stack_trunk(struct Stack* _stack, struct Variable* last){
    if(Stack_rangeValid(_stack, last)){
        int newSize = *(int*)last->value + last->size;
        struct Variable** newVars = malloc(newSize * sizeof(struct Variable *));
        memcpy(newVars, _stack->vars, newSize * sizeof(struct Variable *));
        free(_stack->vars);
        _stack->vars = newVars;
        _stack->size = newSize;
    }
    else {
        printf("Invalid trunk.\n");
        exit(-1);
    }
}

void Stack_safeDeleteRange(struct Stack* _stack, struct Variable* start, struct Variable* end){
    if(Stack_rangeValid(_stack, start) && Stack_rangeValid(_stack, end) && *(int*)end->value != *(int*)start->value){
        int firstBound = *(int*)(start->value + start->size);
        int lastBound = *(int*)(end->value);
        int newSize = _stack->size - (lastBound - firstBound);
        struct Variable** newVars = malloc( newSize * sizeof(struct Variable *));
        // Copying elements between beginning of the stack and firstbound to newVars
        memcpy(newVars, _stack->vars, firstBound * sizeof(struct Variable *));
        // Concat elements between lastbound and the end of the stack with the beginning of newVars
        memmove(newVars + firstBound, _stack->vars + lastBound, (_stack->size - lastBound) * sizeof(struct Variable *));
        // Freeing old stack vars
        free(_stack->vars);
        // Affecting new one
        _stack->vars = newVars;
        _stack->size = newSize;
        // Updating the beginning index of the array pointed by end in the stack
        *(int*)end->value = firstBound;
    }
    else {
        printf("Invalid delete range. \n");
        exit(-1);
    }
}

