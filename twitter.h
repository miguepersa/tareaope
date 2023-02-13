#ifndef TWITTER_H
#define TWITTER_H

#include <stdio.h>
#include <string.h>

#include "htable.h"
#include "tqueue.h"

typedef struct twitter
{
    Htable *usuarios;
    User* loggedUser;
    Tqueue *tweets;
}Twitter;

void twitter_init(Twitter*);
int twitter_login(Twitter*, char*, char*);
void twitter_feed(Twitter*);
void twitter_signup(Twitter*);
void twitter_destroy(Twitter*);
void twitter_print_timeline(User*);
#endif