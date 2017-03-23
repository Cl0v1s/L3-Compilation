#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INT -1
#define BOOL -2
#define ARRAY(size)  ((size) > 0 ? size : 0)

#define false 0
#define true 1

struct Variable
{
    int size;
    void* value;
};

/**
* Initialise une nouvelle variable 
* type : Type de la variable INT|BOOL|ARRAY(taille)
**/
struct Variable* Variable_init(int type);


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