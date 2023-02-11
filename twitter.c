#include "twitter.h"

void twitter_init(Twitter *t)
{
    char username[USERNAME_LIMIT];
    char action[32];
    char password[256];

    t->loggedUser = NULL;

    int run = 1;

    do
    {
        if (t->loggedUser != NULL)
        {
            twitter_feed(t);
        }
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
                if (twitter_login(t, username, password))
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

int twitter_login(Twitter *t, char* username, char* password)
{
    User * u = htable_get_user(t->usuarios, username);
    if (u != NULL)
    {
        if (u->password == hash(password))
        {
            t->loggedUser = u;
            return 1;
        }
    }

    return 0;
}