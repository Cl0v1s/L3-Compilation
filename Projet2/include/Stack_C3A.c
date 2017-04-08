#include "Stack_C3A_C3A.h"

struct Stack_C3A* Stack_C3A_init(){
    struct Stack_C3A* _stack = malloc(sizeof(struct Stack_C3A));
    _stack->values = malloc(0);
    _stack->size = malloc(0);
    _stack->adr = malloc(0);
    _stack->refsLength = 0;
    _stack->valuesLength = 0;
    return _stack;
}

int Stack_C3A_push(struct Stack_C3A* _stack, int size){
    // Getting returned index ( index of the new entry in adr and size arrays )
    int ind = _stack->refsLength;

    // Allocating new arrays and copying old ones
    int* newSize = malloc(refsLength * sizeof(int));
    int* newAdr = malloc(refsLength * sizeof(int));
    int* newValues = malloc((_stack->length + size) * sizeof(int));

    memcpy(newSize, _stack->size, _stack->refsLength * sizeof(int));
    memcpy(newAdr, _stack->adr, _stack->refsLength * sizeof(int));
    memcpy(newValues, _stack->values, _stack->valuesLength * sizeof(int));

    // Then incrementing size of adr and size arrays
    refsLength++;

    // Init
    for(int i = _stack->valuesLength; i < _stack->valuesLength + size; i++){
        newValues[i] = 0;
    }

    _stack->valuesLength = _stack->valuesLength + size;
    // Free old
    free(_stack->values);
    free(_stack->size);
    free(_stack->adr);
    // Affect
    _stack->size = newSize;
    _stack->adr = newAdr;
    _stack->values = newValues;

    return ind;
}

int Stack_C3A_getAvailableIndex(struct Stack_C3A* _stack, int size);

void Stack_C3A_remove(struct Stack_C3A* _stack, int index, int size);


void Stack_C3A_removeArray(struct Stack_C3A* _stack, struct Variable* tab);

/**
 * Stack_C3A_trunk : tronque le Stack_C3A passé le tableau pointé par last
 * @param _stack : le tas
 * @param last : variable pointant sur le dernier tableau de valeurs à garder
 */
void Stack_C3A_trunk(struct Stack_C3A* _stack, struct Variable* last);

/**
 * Stack_C3A_safeDeleteRange : supprime dans le tas les variables entre un tableau et un autre
 * @param _stack
 * @param start
 * @param end
 */
void Stack_C3A_safeDeleteRange(struct Stack_C3A* _stack, struct Variable* start, struct Variable* end);

struct Variable* Stack_C3A_getVariable(struct Stack_C3A* _stack, int index);

void Stack_C3A_setVariable(struct Stack_C3A* _stack, struct Variable* var, int index);


