#ifndef C3A_H
#define C3A_H

#include "utils.h"
#include "Env.h"
#include "Quads.h"
#include "utils.h"
#include "./../c3a.tab.h"

void C3A_run(struct QuadList* list, Env* env);
int C3A_eval(struct Quad* quad, Env* env, struct QuadList* list);



#endif