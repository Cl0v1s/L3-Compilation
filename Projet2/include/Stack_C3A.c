#include "Stack_C3A.h"

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
    int* newSize = malloc(_stack->refsLength * sizeof(int));
    int* newAdr = malloc(_stack->refsLength * sizeof(int));
    int* newValues = malloc((_stack->valuesLength + size) * sizeof(int));

    memcpy(newSize, _stack->size, _stack->refsLength * sizeof(int));
    memcpy(newAdr, _stack->adr, _stack->refsLength * sizeof(int));
    memcpy(newValues, _stack->values, _stack->valuesLength * sizeof(int));

    // Then incrementing size of adr and size arrays
    _stack->refsLength++;

    // Init
    for(int i = _stack->valuesLength; i < _stack->valuesLength + size; i++){
        newValues[i] = 0;
    }
    // Set size and adr
    _stack->adr[ind] = _stack->values[valuesLength];
    _stack->size[ind] = size;
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

void Stack_C3A_setValue(struct Stack_C3A* _stack, int indArr, int indVal, int value){
    if(indArr >= _stack->refsLength){
        printf("Wrong array index ( > refsLength ) in Stack_C3A_setValue. \n");
        exit(-1);
    }
    if(_stack->size[indArr] + indVal >= _stack->valuesLength) {
        printf("Wrong index ( > valuesLength ) in Stack_C3A_setValue. \n");
        exit(-1);
    }

    _stack->values[_stack->adr[indArr] + indVal] = value;
}

int Stack_C3A_getValue(struct Stack_C3A* _stack, int indArr, int indVal){
    if(indArr >= _stack->refsLength){
        printf("Wrong array index ( > refsLength ) in Stack_C3A_setValue. \n");
        exit(-1);
    }
    if(_stack->size[indArr] + indVal >= _stack->valuesLength) {
        printf("Wrong index ( > valuesLength ) in Stack_C3A_setValue. \n");
        exit(-1);
    }
    
    return _stack->values[_stack->adr[indArr] + indVal];
}
