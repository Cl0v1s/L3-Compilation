#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INT -1
#define BOOL -2
#define VOID 0
#define ARRAY 1

#define false 0
#define true 1

struct Variable
{
    int size;
    void* value;
    int item_type;
};

/**
* Initialise une nouvelle variable 
* type : Type de la variable INT|BOOL|ARRAY(taille)
**/
struct Variable* Variable_init(int type);

void Variable_arraySetType(struct Variable* var, int type);

void Variable_set(struct Variable* var, int value);

void Variable_arraySet(struct Variable* var, int index, struct Variable* value);

int Variable_get(struct Variable* var);

struct Variable* Variable_arrayGet(struct Variable* var, int index);

void Variable_print(struct Variable* var);

/**
* Libère la mémoire associée à une variable 
* var: variable sur laquelle opérer
*/
void Variable_free(struct Variable* var);
#endif