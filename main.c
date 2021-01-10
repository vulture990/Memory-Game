#include "textureAndRendering.h"
#include "gamedep.h"
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600


int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("Match Match up V1.0 ",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);     // support for loading PNG and JPEG images
	
	menuLoop(renderer);

	SDL_Delay(1000 / 60); // 30fps
	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
	SDL_FlushEvent(SDL_MOUSEMOTION);
	// Release resources
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
