#ifndef HTABLE_H
#define HTABLE_H

#include "node.h"

#include <string.h>

typedef struct htable
{
    Node* tabla[HTABLE_LIMIT];
    int size;
    
}Htable;

Htable *htable_init();
void htable_add(Htable*, User*);
void htable_destroy(Htable*);

int hash(char*);

#endif