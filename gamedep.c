#include "gamedepen.h"
#include <string.h>
int empty(char *filename, char *mode)
{
    FILE *f = fopen(filename, mode);
    fseek(f, 0L, SEEK_END);
    int vide = (ftell(f) == 0L);
    fclose(f);
    return vide;
}
bool existe(login player)
{
    FILE *f = fopen("C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\user.bin", "rb");
    login user;
    while (1)
    {
        fread(&user, sizeof(user), 1, f);
        if (feof(f))
            break;
        if (strcmp(user.username, player.username) == 0)
            return true;
    }
    fclose(f);
    return false;
}

 bool Signup(signup user)
{
        bool sign;
        user.score = 0;                                                                   //initialize the score to 0
        FILE *f = fopen("C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\user.bin", ab) //path
            if (!f)
        {
            return 0;
        }
        if (empty("C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\user.bin", "ab+") == 1)
        {
            fwrite(&user, sizeof(user), 1, f);
            sign = true;
        }
        else
        {
            login user2;
            strcpy(user2.username, user.username);
            strcpy(user2.motcle, user.motcle);
            user2.score = 0;
            if (existe(user2) == 0)
            {
                fwrite(&user, sizeof(user), 1, f);
                sign = true;
            }
            else
            {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "!!", "already exists :( ", NULL);
                sign = false;
            }
        }
        fclose(f);
        return sign;
}
int login(login player)
{
    FILE *f = fopen("C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\user.bin", "rb");
    if (!f)
    {
        printf("Erreur 404 XD\n");
        exit(0);
    }
    else
        return existe(player);
}
