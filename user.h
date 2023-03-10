/*Archivo que contiene las definiciones de la estructura User*/

#ifndef USER_H
#define USER_H

#include "tweet.h"
#include "tqueue.h"
#include "htable.h"

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

User *user_init();
void user_add_tweet(User*, Tweet*);
void user_destroy(User*);

/*Primer usuario: usuario que quiere seguir a otro. Segundo usuario: usuario al que se quiere seguir.*/
void user_add_following(User*, User*);

#endif