#ifndef USER_H
#define USER_H

#include "tweet.h"
#include "tqueue.h"

typedef struct user
{
    char username[USERNAME_LIMIT];
    int password;
    struct user* following[256];
    Tqueue *tweets;
}User;

User *user_init();
void user_add_tweet(User*, Tweet*);
void user_destroy(User*);

#endif