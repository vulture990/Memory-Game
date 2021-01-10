#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "textureAndRendering.h"
#define inputedStateUsername 0
#define inputedStatePassword 1

//Afin de collecter les info d' utlisateur comme input et crée un compte
typedef struct
{
	char username[30];
	char motcle[30];
	double score;
}signup;
//En cree un compte qui memorise data d'utilisateur
typedef struct
{
	char username[30];
	char motcle[30];
	double score;
}login;
//le status du jeu 
struct gameStatus
{
	bool etat;
};
//parametre du menu du jeu
typedef struct
{
	enumOfButtons isClicked;
	enumOfButtons select;
	int state;
}menu;
//game parametre
typedef struct
{
	int select;
	int click;
	int nombre_letter;
	int nombre_time;
	int score;
}game_parameters;
int empty(char *path, char *mode);
bool exist(login player);
bool Signup(signup user);
bool Login(login user);
