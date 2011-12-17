#include <stdio.h>

#include "Level.h"
#include "SDL/SDL.h"

int doLevel(SDL_Surface* screen)
{
	int quit = 1;

	int i,j;

	int x = 120;
	int y = 120;

	SDL_Surface* buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, 0, 0, 0, 0);

	while(quit)
	{
		SDL_Rect r = {(Sint16)x, (Sint16)y, 16, 16};

		SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 255,255,255));
		
		SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 255, 255));
		SDL_BlitSurface(buffer, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(20);
	}


	SDL_FreeSurface(buffer);
}

