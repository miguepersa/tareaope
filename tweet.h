#ifndef TWEET_H
#define TWEET_H

#include <stdio.h>
#include <time.h>

#include "settings.h"
#include "user.h"

typedef struct tweet
{
    User* user;
    char content[MAX_TWEET];
    int hour;
    int minute;
    int day;
    int month;
}Tweet;

Tweet *tweet_init();
void tweet_print(Tweet*);

#endif