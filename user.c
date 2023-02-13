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

void user_add_following(User* user, User* usertofollow )
{
    int i = 0;

    while(user->following[i] != NULL && i < 257){
        i++;
    }
    
    if(user->following[i] == NULL){
        user->following[i] =usertofollow;

    }else if (i == 257)
    {
        printf("Maxima capacidad alcanzada\n");

    }
    

}