#include <stdio.h>

#include "Level.h"
#include "SDL/SDL.h"

int doLevel(SDL_Surface* screen)
{
	int quit = 1;

	int i,j;

	int x = 120;
	int y = 120;

	int pXSpeed = 0;
	int pYSpeed = 0;

	float runSpeed = 3;

	SDL_Surface* buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, 0, 0, 0, 0);

	while(quit == 1)
	{
		// check for quit event
		while (SDL_PollEvent( &ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = 0;
			}
		}

		// keyboard input
		keystates = SDL_GetKeyState(NULL);
		if (keystates[SDLK_ESCAPE])
		{
			quit = 0;
		}

		if (keystates[SDLK_RIGHT])
		{
			pXSpeed = (int)runSpeed;
		}
		else if (keystates[SDLK_LEFT])
		{
			pXSpeed = (-1)*(int)runSpeed;
		}
		else
		{
			pXSpeed = 0;
		}

		if (keystates[SDLK_DOWN])
		{
			pYSpeed = (int)runSpeed;
		}
		else if (keystates[SDLK_UP])
		{
			pYSpeed = (-1)*(int)runSpeed;
		}
		else
		{
			pYSpeed = 0;
		}

		x += pXSpeed;
		y += pYSpeed;

		SDL_Rect r = {(Sint16)x, (Sint16)y, 16, 16};
		SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 255,255,255));
		
		SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 255, 255));
		SDL_BlitSurface(buffer, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(20);
	}


	SDL_FreeSurface(buffer);

	return 0;
}

