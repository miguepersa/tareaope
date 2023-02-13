#include "user.h"

User* user_init()
{
    User *user = (User*) malloc(sizeof(User));
    if (user == NULL)
    {
        printf("User: malloc error\n");
        return NULL;
    }
    user->followed = 0;
    return u;
}

void user_add_tweet(User* user, Tweet* tweet)
{
    tqueue_add(user->tweets, tweet);
}

void user_destroy(User* user)
{
    free(user);
}

void user_add_following(User* user, User* userToFollow )
{
    int i = 0;

    while(user->following[i] != NULL && i < 257){
        i++;
    }
    
    if(user->following[i] == NULL){
        user->following[i] =userToFollow;

    }else if (i == 257)
    {
        printf("Reached max capacity\n");

    }
    

}