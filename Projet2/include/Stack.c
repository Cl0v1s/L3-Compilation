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

int Stack_push(struct Stack* stack, int sz){

    for(int i = 0; i < stack->refsLength; i++)
    {
        if(stack->adr[i] < 0 && stack->size[i] >= sz)
        {
            printf("Found free space at %d\n", i);
            stack->adr[i] = stack->adr[i] * -1;
            stack->size[i] = sz;
            return i;
        }
    }
    printf("Allocating...\n");

    int index = stack->refsLength;

    int* adr = malloc((stack->refsLength+1)*sizeof(int));
    int* size = malloc((stack->refsLength+1)*sizeof(int));
    int* values = malloc((stack->valuesLength+sz)*sizeof(int));

    memcpy(adr, stack->adr, (stack->refsLength)*sizeof(int));
    memcpy(size, stack->size, (stack->refsLength)*sizeof(int));
    memcpy(values, stack->values, (stack->valuesLength)*sizeof(int));

    adr[index] = stack->valuesLength;
    size[index] = sz;

    for(int i = stack->valuesLength; i < stack->valuesLength+sz; i++)
    {
        values[i] = 0;
    }

    free(stack->adr);
    free(stack->size);
    free(stack->values);

    stack->adr = adr;
    stack->size = size;
    stack->values = values;

    stack->refsLength++;
    stack->valuesLength = stack->valuesLength + sz;

    return index;

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
    printf("Removing.. %d\n", index);
    stack->adr[index] = stack->adr[index] * -1;
    Stack_print(stack);
}

void Stack_print(struct Stack* stack)
{
    printf("Adr: ");
    for(int i = 0; i < stack->refsLength; i++)
    {
        printf("%d,", stack->adr[i]);
    }
    printf("\nsize: ");
    for(int i = 0; i < stack->refsLength; i++)
    {
        printf("%d,", stack->size[i]);
    }
    printf("\nvalues: ");
    for(int i = 0; i < stack->valuesLength; i++)
    {
        printf("%d,", stack->values[i]);
    }
    printf("\n");
}
