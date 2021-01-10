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
	NOT_SELECTED ,
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
Texture* loadTextureText(char* Text, SDL_Color textColor, SDL_Renderer* renderer);
void destroyTexture(Texture* texture);
void render(struct rentxt* r, SDL_Renderer* rendeerer);
enumOfButtons renderMenu(SDL_Renderer *renderer);
//void undo(login user);
void renderTextInxyPlan(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color);
void renderTextOnBox(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color);
void undo(void);
void renderLoginUsername(SDL_Renderer *renderer,char* username);
void renderLoginPassword(SDL_Renderer *renderer, char* password);
void renderLogin(SDL_Renderer* renderer);
void menuLoop(SDL_Renderer* renderer);
//void renderSignup(SDL_Renderer *renderer,char* text);
