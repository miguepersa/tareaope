/*Archivo que contiene las definiciones de la estructura Twitter.*/

#ifndef TWITTER_H
#define TWITTER_H

#include <stdio.h>
#include <string.h>

#include "htable.h"
#include "tqueue.h"
#include "user.h"

typedef struct twitter
{
    Htable *users;
    User* loggedUser;
    Tqueue *tweets;
}Twitter;

void twitter_init(Twitter*);
int twitter_login(Twitter*, char*, char*);
void twitter_feed(Twitter*);
void twitter_signup(Twitter*);
void twitter_print_timeline(Twitter*, User*);
void twitter_destroy(Twitter*);


void clean_stdin(void);

#endif