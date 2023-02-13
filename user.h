#ifndef USER_H
#define USER_H

#include "tweet.h"
#include "tqueue.h"

typedef struct user
{
    char userName[userName_LIMIT];
    int password;
    int followed;
    struct user* following[256];
    Tqueue *tweets;
}User;

User *user_init();
void user_add_tweet(User*, Tweet*);
void user_destroy(User*);
void user_add_following(User*, User*); //Primer usuario: usuario que quiere seguir a otro. Segundo usuario: usuario al que se quiere seguir.

#endif