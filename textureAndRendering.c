#include "textureAndRendering.h"
#include "gamedep.h"
#define DEFAULTFONT "C:\\Users\\vulture\\source\\repos\\Project5\\rsc"
#define PLAYING_PARAMETERS_STATE 1
#define PENDING 0
#define MENUSTATE 0
#define GAMESTATE 1
struct gameStatus running = { true };
game_parameters s;
menu etat;
const SDL_Color black = { .r = 0,.g = 0,.b = 0 };
login loginData;
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
Texture* loadTextureText(char* Text, SDL_Color textColor, SDL_Renderer* renderer)
{

	Texture* texture = (Texture *)malloc(sizeof(Texture));
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
			texture->width = textSurface->w;
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

void render(struct rentxt* r, SDL_Renderer* renderer)
{
	int width, height;
	SDL_Texture * tex = initTexture(r->path, renderer);
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
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
		free(r);
	}
	else
	{
		return No_Clicks;
		free(r);
	}

}

void renderLoginUsername(SDL_Renderer *renderer, char* text)
{
	SDL_StartTextInput();
	etat.state = inputedStateUsername;
	SDL_Event event;
	while (SDL_PollEvent(&event) && etat.state == inputedStateUsername)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running.etat = false;
			break;
		case SDL_TEXTINPUT: //  input from keyboard
			if (strlen(text) < 31)
			{
				strcat(text, event.text.text);
				break;
			}
		case SDL_KEYDOWN: // lol edge cases
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE: // go back to write username again 
				etat.select = NOT_SELECTED;
				etat.state = inputedStateUsername;
					break;
			case SDL_SCANCODE_BACKSPACE: // we wanna delete the last element by doing this :
				text[strlen(text) - 1] = 0;
				break;
			case SDL_SCANCODE_RETURN:
				etat.state = inputedStatePassword;
				SDL_StopTextInput();
				break;
			}
		}
	}
	renderTextInxyPlan(renderer, text, 350,315 , black);
}
//void undoLogin(login user)//basicly it reset the data to 0 
//{
//	int i = 0;
//	while (i < 31) {
//		user.username[i] = NULL;
//		user.motcle[i] = NULL;
//		user.score = 0;
//		i++;
//	}
//	etat.state=;
//}



void renderTextInxyPlan(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color) 
{
	TTF_Init();
	TTF_Font * font = TTF_OpenFont(DEFAULTFONT, 17);
	SDL_Rect dest;
	dest.x = x; dest.y = y;
	SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}
// render a text inside a box
void renderTextOnBox(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color) 
{
	TTF_Init();
	TTF_Font * font = TTF_OpenFont(DEFAULTFONT, 40);
	SDL_Rect dest;
	dest.x = x; dest.y = y;
	SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void undo(void)
{
	int i = 0;
	while (i < 25)
	{
		loginData.username[i] = 0;
		loginData.motcle[i] = 0;
		i++;
	}
	etat.state = inputedStateUsername;
}


void renderLoginPassword(SDL_Renderer* renderer, char* text)
{
	SDL_StartTextInput();
	SDL_Event event;
	etat.state = inputedStatePassword;
	while (SDL_PollEvent(&event) && etat.state == inputedStatePassword)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running.etat = false;
			break;
		case SDL_TEXTINPUT:
			if (strlen(text < 31))
			{
				strcat(text, event.text.text);
				break;
			}
		case SDL_KEYDOWN: // lol edge cases
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE: // go back to write username again 
				etat.select = NOT_SELECTED;
				etat.state = inputedStatePassword;
				break;
			case SDL_SCANCODE_BACKSPACE: // we wanna delete the last element by doing this :
				text[strlen(text) - 1] = 0;
				break;
			case SDL_SCANCODE_RETURN:
				if (Login(loginData) == 1) { // if login data is correct
					s.select= PLAYING_PARAMETERS_STATE; // move rendrer to playing sceen
					etat.select = NOT_SELECTED;
					etat.isClicked = NOT_SELECTED;
					SDL_StopTextInput();
				}
				else 
				{
					undo();
					SDL_StopTextInput();
				}
				break;
			}
		}
	}
	renderTextInxyPlan(renderer, loginData.username, 340, 315, black);
}

void renderLogin(SDL_Renderer *renderer)
{
	struct rentxt *r = (struct rentxt*)malloc(sizeof(struct rentxt));
	r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\login_bar.jpg";
	r->x = 0;
	r->y = 0;
	render(r, renderer);
	free(r);
	r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\login.png";
	r->x = 329;
	r->y = 470;
	render(r, renderer);
	free(r);
	switch (etat.state)
	{
	case inputedStateUsername:
		renderLoginUsername(renderer, loginData.username);
	case inputedStatePassword:
		renderLoginPassword(renderer, loginData.motcle);

		// getting the position of mouse clicks(hovering)        
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		if (mouse_x > 329 && mouse_x < 329 + LOGIN_X && mouse_y > 479 && mouse_y < 479 + LOGIN_Y)
		{
			r->path = "C:\\Users\\vulture\\source\\repos\\Project5\\rsc\\login.png";
			r->x = 329 + 4;
			r->y = 470 + 9;
			render(r, renderer);
			free(r);
		}
	}
}


void menuLoop(SDL_Renderer *renderer)
{
	etat.state = MENUSTATE;
	running.etat = true;
	SDL_Event event;
	while (running.etat && etat.state == MENUSTATE)
	{
		while (SDL_PollEvent(&event))
		{
			// Process events
			switch (event.type)
			{
			case SDL_QUIT:
				running.etat = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				etat.select = etat.isClicked; // assigning where the mouse was hovered to be selected
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE: // Escape + return keys => return to menu
					etat.select = NOT_SELECTED;
					break;
				}
			}
		}
		SDL_RenderClear(renderer);
		switch (etat.select) {
		case NOT_SELECTED:
			etat.isClicked = render_menu(renderer); 
			break;
		case Login_Confirmed:
			renderLogin(renderer);
			break;
		}
		SDL_RenderPresent(renderer);  // Last but not least show the renderer
	}

}
