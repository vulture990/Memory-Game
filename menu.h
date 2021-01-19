#pragma once
#include <stdbool.h> 
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
    
GtkBuilder* builder;

GtkWidget* username;
GtkWidget* password;
FILE* fp=NULL;


typedef struct
{
        char username[30];
        char password[30];
        double score;
        // GtkWidget* Login;
        bool getAcessToPlay;
}login; 

typedef struct
{
        char username[30];
        char password[30];
        double score;
        GtkWidget* SignUp;  
          
        
}signup 

typedef enum
{
        bool menuPhase;
        bool gamePhase;
}gameState;

static void SignUp(GtkWiget* widget,gpointer data,signup s);
          
bool empty(char* nameFile,char* mode);

bool exist(login user);

bool isLogged(login usr);

