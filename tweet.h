#ifndef TWEET_H
#define TWEET_H

#include "settings.h"
#include "user.h"

typedef struct tweet
{
    User* u;
    char contenido[MAX_TWEET];
    struct tweet respuestas[1024];
}Tweet;


#endif