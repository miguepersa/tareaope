#ifndef USER_H
#define USER_H

#include "tweet.h"

typedef struct user
{
    char username[USERNAME_LIMIT];
    char password[256];
    struct user* following[256];
}User;

void user_destroy(User*);

#endif