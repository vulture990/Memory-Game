#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDl_image.h>
#include <SDL_ttf.h>
TTF_Font* font;
int const MENU_X = 0;
int const MENU_Y = 0;
int const LOGIN_X = 450;
int const LOGIN_Y = 350;
int const SIGNUP_X = 300;
int const SIGNUP_Y = 325;
typedef enum
{
	Login_Confirmed,
	Signup_Confirmed,
	No_Clicks

}enumOfButtons;
// on aura besoin de ces parametre afin de charger texture.. for fonts...
typedef struct
{
	SDL_Texture* texture;
	char* path;
	int width;
	int height;
}Texture;
  struct rentxt
{
	int x;
	int y;
	char* path;
};
//for rendering in x,y plan

SDL_Texture *initTexture(const char *path, SDL_Renderer *renderer);
//this one is a utility function to charge the font
void chargeFont(char* text, int scale);
Texture* loadTextureText(char* Text, SDL_Color textColor,SDL_Renderer* renderer );
void destroyTexture(Texture* texture);
void render(struct rentxt* r,SDL_Renderer* rendeerer); 
enumOfButtons renderMenu(SDL_Renderer *renderer);
void renderLogin(SDL_Renderer *renderer);
void renderSingup(SDL_Renderer *renderer);
