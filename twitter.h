#ifndef TWITTER_H
#define TWITTER_H

#include <stdio.h>
#include <string.h>

#include "htable.h"
#include "tqueue.h"

typedef struct twitter
{
    Htable usuarios;
    User* u;
    Tqueue *tweets;
}Twitter;

void twitter_init(Twitter*);
int twitter_login(char*, char*, User*);
void twitter_feed(Twitter*);
void twitter_signup(Twitter*);

#endif