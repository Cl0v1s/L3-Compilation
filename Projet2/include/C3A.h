//
// Created by clovis on 08/04/17.
//

#include "./../c3ainterpret.tab.h"
#include "Quads.h"
#include "Stack_C3A.h"
#include "Env_C3A.h"

#ifndef L3_COMPILATION_C3A_H
#define L3_COMPILATION_C3A_H

void C3A_run(struct QuadList* quads, struct Env_C3A* env);
struct Quad* C3A_eval(struct Quad* quad, Env* env, struct QuadList* list);
#endif //L3_COMPILATION_C3A_H
