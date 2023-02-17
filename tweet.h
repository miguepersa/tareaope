#ifndef TWEET_H
#define TWEET_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "settings.h"
#include "htable.h"


typedef struct tweet
{
    char content[MAX_TWEET];
    User *u;
    int hour;
    int minute;
    int day;
    int month;
}Tweet;

Tweet *tweet_init();
void tweet_print(Tweet*);

#endif