#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDl_image.h>
#include <SDL_ttf.h>


typedef struct
{
	SDL_Texture* texture;
	char* path;
	int width;
	int height;
}Texture;


SDL_Texture *initTexture(const char *path, SDL_Renderer *renderer);
Texture* loadTextureText(char* Text, SDL_Color textColor);
void demolishTexture(Texture* texture);
void render(const char *path, SDL_Renderer *renderer, int x, int y); // rendering texture in (x,y) plane
int renderMenu(SDL_Renderer *renderer);
void renderLogin(SDL_Renderer *renderer);
void renderSingup(SDL_Renderer *renderer);
