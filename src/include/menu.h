#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>


// GtkWidget* username;
// GtkWidget* password;
// typedef struct 
// {
//     GtkWidget* window;
//     GtkWidget* window2;
// }windows;


extern GtkBuilder *builder;
extern GtkWidget* username;
extern GtkWidget* password;
extern GtkWidget* usernameLogin;
extern GtkWidget* passwordLogin;

extern GtkWidget* window;
extern GtkWidget* window2;
extern GtkWidget* window3;
extern GtkWidget* button6;
extern GtkWidget* button1;
extern GtkWidget* button2;
extern GtkWidget* button3;
extern GtkWidget* button4;
extern GtkWidget* button5;
extern GtkWidget* button7;
extern GtkWidget* button77;
extern FILE *fp;
extern GtkWidget* usernameLogin;
extern GtkWidget* passwordLogin;
// extern signup *user;

// extern login *userr;

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

}signup;

// typedef enum
// {
//         bool menuPhase;
//         bool gamePhase;
// }gameState;
void LOGIN(GtkButton *button, gpointer data);
void SIGNUP(GtkButton *button, gpointer data);
int empty(char *filename, char *mode);
void menu(void);
void MENU(GtkButton *button, gpointer data);
bool exist(login player,char* filename,char* mode);
// void SignUp(GtkWidget *Widget, gpointer data);
bool isSigned(login player);
#endif
