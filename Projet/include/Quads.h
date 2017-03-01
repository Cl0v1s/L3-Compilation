#ifndef QUADS_H
#define QUADS_H 

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Env.h"
#include "utils.h"


struct Value{
    char type;
    void *value;
};

struct Quad{
  char *address;
  int  operation;
  struct Value* arg1;
  struct Value* arg2; 
  char* destination;
  struct Quad *next;
  };

struct QuadList{
  struct Quad* start;
  struct Quad* end;
};


struct Value* Value_create(char type, void* value);

int Value_get(struct Value* value, Env* env);

void Value_delete(struct Value* value);


struct QuadList* QuadList_create(struct Quad* quad);

void QuadList_delete(struct QuadList* list);

void QuadList_deleteAll(struct QuadList* list);

struct QuadList* QuadList_concat(struct QuadList* first, struct QuadList* second);

struct Quad* QuadList_search(struct QuadList* list, char* address);

struct Quad* Quad_create(char* address, int ope, struct Value* arg1, struct Value* arg2, char* destination);

int Quad_hasAddress(struct Quad* quad, char* address);

void Quad_delete(struct Quad* quad);





#endif