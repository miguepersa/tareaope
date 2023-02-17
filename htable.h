#ifndef HTABLE_H
#define HTABLE_H

#include "node.h"
#include "settings.h"
/*#include "user.h"*/

#include <string.h>

typedef struct user User;

typedef struct htable
{
    Node* table[HTABLE_LIMIT];
    int size;
    
}Htable;

Htable *htable_init();
void htable_add(Htable*, User*);
User *htable_get_user(Htable*, char*);
void htable_destroy(Htable*);

int hash(char*);

#endif