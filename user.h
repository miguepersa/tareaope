#ifndef USER_H
#define USER_H

#include "tweet.h"

typedef struct user
{
    char username[USERNAME_LIMIT];
    struct user* following[256];
}User;


#endif