#include "twitter.h"

void twitter_init(Twitter *t)
{
    char username[USERNAME_LIMIT];
    char action[32];
    char password[256];

    int run = 1;

    do
    {
        printf("DON'T MISS WHAT'S HAPPENING! LOGIN, SIGNUP OR LEAVE\n");

        scanf("%s\n", action);

        if (strcmp(action, "login") == 0)
        {
            while (1)
            {
                printf("USERNAME: ");
                scanf("%s\n", username);
                printf("PASSWORD: ");
                scanf("%s\n", password);
                if (twitter_login(username, password, t->u))
                {
                    break;
                }
                else
                {
                    printf("Invalid credentials, try again\n");
                }
            }
            
            
        } else if (strcmp(action, "signup") == 0);
        {
            twitter_signup(t);
        }
        
    }while (run);
            
}