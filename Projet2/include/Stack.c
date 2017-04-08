#include "Stack.h"

struct Stack* Stack_init(){
    struct Stack* _stack = malloc(sizeof(struct Stack));
    _stack->values = malloc(0);
    _stack->size = malloc(0);
    _stack->adr = malloc(0);
    _stack->refsLength = 0;
    _stack->valuesLength = 0;
    return _stack;
}

int Stack_push(struct Stack* _stack, int size){

    for(int i = 0; i < _stack->refsLength; i++)
    {
        if(_stack->adr[i] < 0 && _stack->size[i] >= size)
        {
            _stack->adr[i] = _stack->adr[i] * -1;
            _stack->size[i] = size;
            return i;
        }
    }

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

void Stack_setValue(struct Stack* _stack, int index, int value)
{
    if(index >= _stack->valuesLength)
    {
        printf("STACK: Index out of range.\n");
        exit(-1);
    }
    _stack->values[index] = value;
}

int Stack_getValue(struct Stack* _stack, int index)
{
    if(index >= _stack->valuesLength)
    {
        printf("STACK: Index out of range.\n");
        exit(-1);
    }
    return _stack->values[index];
}

void Stack_remove(struct Stack* stack, int index)
{
    stack->adr[index] = stack->adr[index] * -1;
}
