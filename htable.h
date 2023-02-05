#ifndef HTABLE_H
#define HTABLE_H

#include "node.h"

typedef struct htable
{
    Node* tabla[HTABLE_LIMIT];
    int size;
    
}Htable;


#endif