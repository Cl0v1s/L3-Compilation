#include "Quads.h"


struct Value* Value_create(char type, void* value)
{
    struct Value* obj = malloc(sizeof(struct Value));
    obj->type = type;
    if(type == 'I' || type=='B')
    {
        int* tmp = malloc(sizeof(int));
        memcpy(tmp, value, sizeof(int));
        value=tmp;
    }
    else if(type == 'V')
    {
        value = strdup(value);
    }
    obj->value = value;
}

int Value_get(struct Value* value, struct EnvC3A* env, struct Stack* stack, int* adr, int* size, int index)
{
    int tmp;
    switch(value->type)
    {
        case 'V':
            if(EnvC3A_key_exists(env, (char*)value->value) == false)
            {
                printf("Variable '%s' indéfinie.\n", (char*)value->value);
                exit(1);
            }
            tmp = EnvC3A_get_value(env, (char*)value->value);
            *adr = stack->adr[tmp];
            *size = stack->size[tmp];
            return Stack_getValue(stack, *adr+index);
        case 'I':
        case 'B':
            return *(int*)value->value;
    }
}

void Value_delete(struct Value* value)
{
    free(value->value);
    free(value);
}

struct QuadList* QuadList_create(struct Quad* quad)
{
    struct QuadList* list = malloc(sizeof(struct QuadList));
    list->start = quad;
    list->end = quad;
    return list;
}

struct QuadList* QuadList_concat(struct QuadList* first, struct QuadList* second)
{
    struct QuadList* list = malloc(sizeof(struct QuadList));
    first->end->next = second->start;
    list->start = first->start;
    list->end = second->end;
    QuadList_delete(first);
    QuadList_delete(second);
    return list;
}

struct Quad* QuadList_search(struct QuadList* list, char* address)
{
    //printf("Search in %p\n", list->start);
    struct Quad* current = list->start;

    do
    {
        //printf("Search: %s | current %p\n", address, current->address);
        if (Quad_hasAddress(current, address) == true)
            return current;
        current = current->next;
    }
    while(list->start != list->end && current != 0 && current != list->start);
    return 0;
}


void QuadList_delete(struct QuadList* list)
{
    free(list);
}

void QuadList_deleteAll(struct QuadList* list)
{
    struct Quad* current = list->start;
    struct Quad* next;
    do
    {
        printf("free %p\n", current);
        next = current->next;
        Quad_delete(current);
        current = next;
    }
    while(list->start != list->end && current != 0);
    free(list);
}

struct Quad* Quad_create(char* address, int ope, struct Value* arg1, struct Value* arg2, char* destination)
{
    struct Quad* quad = malloc(sizeof(struct Quad));
    quad->address = address;
    quad->operation = ope;
    quad->arg1 = arg1;
    quad->arg2 = arg2;
    quad->destination = destination;
    quad->next = 0;
}

int Quad_hasAddress(struct Quad* quad, char* address)
{
    if(quad->address == 0)
        return false;
    if(strcmp(quad->address, address) == 0)
        return true;
    else return false;
}

void Quad_setAddress(struct Quad* quad, char* value)
{
    int len = strlen(value) + 1;
    char* tmp = malloc(len*sizeof(char));
    memcpy(tmp, value, len*sizeof(char));
    quad->address = tmp;
}

void Quad_delete(struct Quad* quad)
{
    free(quad->address);
    Value_delete(quad->arg1);
    Value_delete(quad->arg2);
    free(quad->destination);
}