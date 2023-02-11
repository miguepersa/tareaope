#include "user.h"

User* user_init()
{
    User *u = (User*) malloc(sizeof(User));
    if (u == NULL)
    {
        printf("User: malloc error\n");
        return NULL;
    }
    u->followed = 0;
    return u;
}

void user_add_tweet(User* u, Tweet* t)
{
    tqueue_add(u->tweets, t);
}

void user_destroy(User* u)
{
    free(u);
}