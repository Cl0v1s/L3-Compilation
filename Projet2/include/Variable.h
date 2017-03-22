#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdlib.h>
#include <stdio.h>

#define INT 0
#define BOOL 0
#define ARRAY(size)  ((size) > 0 ? size : -1))

#define false 0
#define true 1

struct Variable
{
    int size;
    void* value;
}

/**
* Initialise une nouvelle variable 
* type : Type de la variable INT|BOOL|ARRAY(taille)
**/
struct Variable* Variable_init(int type);


void Variable_set(struct Variable* var, int* value);

void Variable_arraySet(struct Variable* var, int index, void* value);

/**
* Libère la mémoire associée à une variable 
* var: variable sur laquelle opérer
*/
void Variable_free(struct Variable* var);
#endif