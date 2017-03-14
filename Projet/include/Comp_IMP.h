#ifndef COMP_IMP_H
#define COMP_IMP_H

#include <stdio.h>

#include "Quads.h"
#include "Ast.h"

/**
* Compile un programe IMP en programme C3A
* imp: programme IMP 
**/
void IMP_Compile_C3A(struct Ast* imp);

#endif