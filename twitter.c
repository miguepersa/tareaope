#include "twitter.h"

void twitter_init(Twitter *twitter)
{
    twitter->users = htable_init();
    twitter->tweets = tqueue_init();
    twitter->loggedUser = NULL;
    char userName[USERNAME_LIMIT];
    char action[32];
    char password[256];

    twitter->loggedUser = NULL;

    int run = 1;

    do
    {
        if (twitter->loggedUser != NULL)
        {
            twitter_feed(twitter);
        }
        printf("DON'T MISS WHAT'S HAPPENING! LOGIN, SIGNUP OR LEAVE\n");

        scanf("%s", action);
        fflush(stdin);

        if (strcmp(action, "login") == 0)
        {
            while (1)
            {
                printf("userName: ");
                scanf("%s", userName);
                printf("PASSWORD: ");
                scanf("%s", password);
                if (twitter_login(twitter, userName, password))
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
            twitter_signup(twitter);
        } else if (strcmp(action, "leave") == 0)
        {
            run = 0;
            twitter_destroy(twitter);
        }
        
    }while (run);
            
}

int twitter_login(Twitter *twitter, char* userName, char* password)
{
    User * currentUser = htable_get_user(twitter->users, userName);
    if (currentUser != NULL)
    {
        if (currentUser->password == hash(password))
        {
            twitter->loggedUser = currentUser;
            return 1;
        }
    }

    return 0;
}

void twitter_feed(Twitter* twitter)
{
    char input[8];

    twitter_print_timeline(twitter, twitter->loggedUser);
    int follow = 0;
    User* toFollow = NULL;

    while(1){

        printf("WHAT'S HAPPENING?\n");
        scanf("%s", input);

        if (input[0] == '+' && strlen(input) == 1)
        {
            clean_stdin();
            Tweet * tweet = tweet_init();

            time_t inittime;
            struct tm *info;
            time( &inittime );
            info = localtime( &inittime );

            tweet->day = info->tm_mday;
            tweet->month = info->tm_mon;
            tweet->hour = info->tm_hour;
            tweet->minute = info->tm_min;
            tweet->u = twitter->loggedUser;

            printf("Input the tweet (max 280 chars): ");
            scanf("%[^\n]", tweet->content);
            
            tqueue_add(twitter->loggedUser->tweets, tweet);
            tqueue_add(twitter->tweets,tweet);


        } else if (input[0] == '@' && strlen(input) == 1)
        {
            clean_stdin();
            char userName[USERNAME_LIMIT];
            printf("Give me an userName: ");
            scanf("%s", userName);

            toFollow = htable_get_user(twitter->users, userName);

            if (toFollow == NULL){
                printf("There's no user with that name\n");

            }else{
                printf("@%s\n", toFollow->userName);
                tqueue_print(toFollow->tweets);
                follow = 1;

            }
            
            

        } else if (strcmp(input, "logout") == 0)
        {
            clean_stdin();
            twitter->loggedUser = NULL;
            break;
        }else if(strcmp(input, "follow") == 0 && follow == 1){
            clean_stdin();
            if (htable_get_user(twitter->loggedUser->following, toFollow->userName) != NULL)
            {
                printf("Already following user @%s\n", toFollow->userName);
            } else
            {
                htable_add(twitter->loggedUser->following, toFollow);
                twitter->loggedUser->followed++;
                printf("Now you follow @%s!\n",toFollow->userName);
            }
            follow = 0;

        }


    clean_stdin();

    }
    
}

void twitter_signup(Twitter* twitter)
{
    User *user = user_init();
    char buff[256];

    printf("userName: ");
    scanf("%s", user->userName);
    printf("password: ");
    scanf("%s", buff);

    user->password = hash(buff);

    htable_add(twitter->users, user);
}

void twitter_print_timeline(Twitter *t, User* user)
{
    Tnode *aux = t->tweets->head;

    while (aux != NULL)
    {
        if (htable_get_user(user->following, aux->tweet->u->userName))
        {
            tweet_print(aux->tweet);
        }
        aux = aux->next;
    }
    
}

void twitter_destroy(Twitter* twitter)
{
    htable_destroy(twitter->users);
    tqueue_destroy(twitter->tweets);
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}