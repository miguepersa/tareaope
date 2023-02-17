#ifndef HTABLE_H
#define HTABLE_H

#include "node.h"
#include "settings.h"
#include "tqueue.h"

#include <string.h>

typedef struct htable
{
    Node* table[HTABLE_LIMIT];
    int size;
    
}Htable;

#ifndef USER
#define USER
typedef struct user
{
    char userName[USERNAME_LIMIT];
    int password;
    int followed;
    Htable *following;
    Tqueue *tweets;
}User;

#endif

Htable *htable_init();
void htable_add(Htable*, User*);
User *htable_get_user(Htable*, char*);
void htable_destroy(Htable*);

int hash(char*);

#endif