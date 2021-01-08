#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
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
struct game_status
{
    bool etat;
};
//parametre du menu du jeu
typedef struct 
{
    int click;
    int select;
    int input_state;
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
int empty(char *path, char *mode) ;
bool existe(login player) ;
int Signup(signup user);
int Login(login user);


