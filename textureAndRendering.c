#include "textureAndRendering.h"

SDL_Texture *initTexture(const char *path, SDL_Renderer *renderer)
{
	//creating surface to load the texture

	SDL_Surface* img = IMG_Load(path);
	SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(render, img);
	return imgTexture;
}

void chargeFont(char* text, int scale)
{
	font = TTF_OpenFont(text, scale);
}
//load texture from text
Texture* loadTextureText(char* Text, SDL_Color textColor,SDL_Renderer* renderer)
{

	Texture* texture =(Texture *) malloc(sizeof(Texture));
	texture->path = Text;
	SDL_Surface* textSurface = NULL;
	//Render text surface

	if (Text == "") textSurface = TTF_RenderText_Solid(font, " ", textColor);
	else
	{
		textSurface = TTF_RenderText_Solid(font, Text, textColor);
	}

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return NULL;
	}
	else
	{
		//Create texture from surface pixels
		texture->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			texture->width= textSurface->w;
			texture->height = textSurface->h;
		}
		//flush out this sucker
		SDL_FreeSurface(textSurface);
	}
	return texture;
}

void destroyTexture(Texture* texture)
{
	SDL_DestroyTexture(texture->texture);
	free(texture);
}

//rendering on a chosen (x,y) plane

void render(struct rentxt* r,SDL_Renderer* renderer)
{
	int width, height;
	SDL_Texture * tex = initTexture(r->path, renderer);
	SDL_QueryTexture(tex, NULL, NULL,&width,&height);
	SDL_Rect mouseClick;
	mouseClick.x = r->x;
	mouseClick.y = r->y;
	mouseClick.w = width;
	mouseClick.h = height;
	SDL_RenderCopy(renderer, tex, NULL, &mouseClick);
	SDL_DestroyTexture(tex);
}


enumOfButtons renderMenu(SDL_Renderer* renderer)
{
	struct rentxt* r = (struct rentxt *)malloc(sizeof(struct rentxt));
	r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\menu.png";//it's local path
	r->x = MENU_X;
	r->y = MENU_Y;
	render(r->path, renderer, r->x, r->y);
	r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\login.png";
	r->x = LOGIN_X;
	r->y = LOGIN_Y;
	render(r->path, renderer, r->x, r->y);
	r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\signup";
	r->x = SIGNUP_X;
	r->y = SIGNUP_Y;
	render(r->path, renderer, r->x, r->y);
	int xClick, yClick;
	SDL_GetMouseState(&xClick, &yClick);
	if (xClick > LOGIN_X &&xClick<LOGIN_X + 10 && yClick>LOGIN_Y && yClick < LOGIN_Y + 10)
	{
		r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\login.png";
		r->x = LOGIN_X;
		r->y = LOGIN_Y;
		render(r, renderer);
		return Login_Confirmed;
	}
	if (xClick > SIGNUP_X && xClick < SIGNUP_X + 10 && xClick<SIGNUP_Y + 10 && yClick>SIGNUP_Y)
	{
		r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\signup";
		r->x = SIGNUP_X;
		r->y = SIGNUP_Y;
		render(r, renderer);
		return Signup_Confirmed;
	}
	free(r);
	else
	{
		return No_Clicks;
	}
}
