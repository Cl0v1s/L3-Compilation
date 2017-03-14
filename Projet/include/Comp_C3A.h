#ifndef Comp_C3A_H
#define Comp_C3A_H

#include "utils.h"
#include "Env.h"
#include "Quads.h"
#include "./../comp_c3a.tab.h"

int Comp_C3A_countInstructions(struct QuadList* list);

Env* Comp_C3A_declareVariables(struct QuadList* list, int * memoryend);

void C3A_Compile_Y86(struct QuadList* list);
void Comp_C3A_translate(struct Quad* quad, int memorystart, Env* variablesOffset);

#endif 