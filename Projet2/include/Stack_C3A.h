#ifndef STACK_C3A_H
#define STACK_C3A_H


struct Stack_C3A
{
    int* values;
    int* adr;
    int* size;
    int refsLength;
    int valuesLength;
};

struct Stack_C3A* Stack_C3A_init();

int Stack_C3A_push(struct Stack_C3A* _stack, int size);

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



#endif //STACK_C3A_H
