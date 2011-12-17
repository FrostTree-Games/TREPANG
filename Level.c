#include <stdio.h>

#include "Level.h"
#include "SDL/SDL.h"

void updatePlayerLogic(Uint32 currTime)
{
	Uint32 tDiff = currTime - pLastTime;
	
	float pXSpeed = 0.0f;
	float pYSpeed = 0.0f;

	if (keystates[SDLK_RIGHT])
	{
		pXSpeed = runSpeed;
	}
	else if (keystates[SDLK_LEFT])
	{
		pXSpeed = -runSpeed;
	}
	else
	{
		pXSpeed = 0.0f;
	}

	if (keystates[SDLK_DOWN])
	{
		pYSpeed = runSpeed;
	}
	else if (keystates[SDLK_UP])
	{
		pYSpeed = -runSpeed;
	}
	else
	{
		pYSpeed = 0.0f;
	}

	px += (int)((pXSpeed/1000.0)*tDiff);
	py += (int)((pYSpeed/1000.0)*tDiff);
	pLastTime = currTime;
}

int doLevel(SDL_Surface* screen)
{
	int quit = 1;

	int i,j;

	px = 120;
	py = 120;

	pLastTime = SDL_GetTicks();

	runSpeed = 100.0f;

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

		// time diff
		Uint32 currTicks = SDL_GetTicks();

		updatePlayerLogic(currTicks);

		SDL_Rect r = {(Sint16)px, (Sint16)py, 16, 16};
		SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 255,255,255));
		
		SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 255, 255));
		SDL_BlitSurface(buffer, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(20);
	}


	SDL_FreeSurface(buffer);

	return 0;
}

