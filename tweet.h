#ifndef TWEET_H
#define TWEET_H

#include <stdio.h>
#include <time.h>

#include "settings.h"
#include "user.h"

typedef struct tweet
{
    User* u;
    char contenido[MAX_TWEET];
    char time[32];
}Tweet;

Tweet *tweet_init();

#endif