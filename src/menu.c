#include "menu.h"


int empty(char *filename, char *mode)
{
	FILE *f = fopen(filename, mode);
	fseek(f, 0L, SEEK_END);
	int vide = (ftell(f) == 0L);
	fclose(f);
	return vide;
}


bool exist(login player)
{

    FILE *f=fopen("user.bin","rb");
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





static void SignUp(GtkWidget *Widget, gpointer data,signup user)
{
  user.score=0;
  strcpy(user.username, gtk_entry_get_text(GTK_ENTRY(username)));
  strcpy(user.password, gtk_entry_get_text(GTK_ENTRY(password)));
  fp=fopen("user.bin","ab");
  if(fp!=NULL)
  {
      if (empty("user.bin", "ab+") == 1)
	{
		fwrite(&user, sizeof(user), 1, fp);
	}
	else
	{
		login user2;
		strcpy(user2.username, user.username);
		strcpy(user2.password, user.password);
		user2.score = 0;
		if (exist(user2) == 0)
		{
			fwrite(&user, sizeof(user), 1, fp);
			
        }
    fclose(fp);
  
}



bool islogged(login player)
{
	FILE *f = fopen("user.bin", "rb");
	if (!f)
	{
		printf("Erreur 404 XD\n");
		exit(0);
	}
	else
    {
        player.getAcessToPlay=true;
		return exist(player);
    }
}
