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
            
            
        } else if (strcmp(action, "signup") == 0)
        {
            twitter_signup(t);
        } else if (strcmp(action, "leave") == 0)
        {
            run = 0;
            twitter_destroy(t);
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

void twitter_feed(Twitter* t)
{
    char input[8];

    tqueue_print(t->tweets, t->loggedUser);

    printf("WHAT'S HAPPENING?\n");
    scanf("%s", input);

    if (input[0] == '+' && strlen(input) == 1)
    {
        Tweet * tw = tweet_init();
        tw->u = t->loggedUser;

        time_t inittime;
        struct tm *info;
        time( &inittime );
        info = localtime( &inittime );

        tw->day = info->tm_mday;
        tw->month = info->tm_mon;
        tw->hour = info->tm_hour;
        tw->minute = info->tm_min;


        printf("Input the tweet (max 280 chars): ");
        scanf("%s", tw->contenido);
        tw->contenido[280] = '\0';


    } else if (input[0] == '@' && strlen(input) == 1)
    {
        char username[USERNAME_LIMIT];
        printf("Give me an username: ");
        scanf("%s", username);

        User * user = htable_get_user(t->usuarios, username);
        if (user == NULL){
            printf("There's no user with that name\n");

        }else{
            tqueue_print(user->tweets)

        }
        

    } else if (strcmp(input, "logout") == 0)
    {

    }
    
}

void twitter_signup(Twitter* t)
{
    User *u = user_init();
    char buff[256];

    printf("username: ");
    scanf("%s", u->username);
    printf("password: ");
    scanf("%s", buff);

    u->password = hash(buff);

    htable_add(t->usuarios, u);
}