#ifndef TWEET_H
#define TWEET_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "settings.h"

typedef struct user User;

typedef struct tweet
{
    char content[MAX_TWEET];
    int hour;
    int minute;
    int day;
    int month;
}Tweet;

Tweet *tweet_init();
void tweet_print(Tweet*);

#endif