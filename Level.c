#include <stdio.h>

#include "Level.h"
#include "SDL/SDL.h"

int hitTest(aX, aY, aW, aH, bX, bY, bW, bH)
{
	if (aY + aH <= bY || aY >= bY + bH)
	{
		return 0;
	}

	if (aX + aW <= bX || aX >= bX + bW)
	{
		return 0;
	}

	return 1;
}

void updatePlayerLogic(Uint32 currTime)
{
	int i;

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

	for (i = 0; i < blockCount; i++)
	{
		if (hitTest(px, py, 16, 16, blockList[i].x, blockList[i].y, 16, 16))
		{
			if (pXSpeed != 0.0f)
			{
				px -= (int)((pXSpeed/1000.0)*tDiff);
			}
			if (pYSpeed != 0.0f)
			{
				py -= (int)((pYSpeed/1000.0)*tDiff);
			}
		}
	}

	pLastTime = currTime;
}

void drawVisuals()
{
	int i;

	SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 255,255,255));

	SDL_Rect r = {(Sint16)(buffer->w)/2, (Sint16)(buffer->h)/2, 16, 16};
	SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 255, 255));

	for (i = 0; i < blockCount; i++)
	{
		if (blockList[i].x > px - (buffer->w)/2 - 16 && blockList[i].x < px + (buffer->w)/2)
		{
			if (blockList[i].y > py - (buffer->h)/2 - 16 && blockList[i].y < py + (buffer->h)/2)
			{
				SDL_Rect r = {(Sint16)(blockList[i].x - px + ((buffer->w)/2)), (Sint16)(blockList[i].y - py + ((buffer->h)/2)), 16, 16};
				SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 0, 0));
			}
		}
	}
}

int doLevel(SDL_Surface* screen, int levelWidth, int levelHeight)
{
	int quit = 1;

	int i;

	px = 120;
	py = 120;

	blockCount = 5;
	blockList = malloc(blockCount * sizeof(struct block));
	for (i = 0; i < blockCount; i++)
	{
		blockList[i].x = i * 32;
		blockList[i].y = 64;
	}

	pLastTime = SDL_GetTicks();

	runSpeed = 100.0f;

	buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, 0, 0, 0, 0);

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

		drawVisuals();

		SDL_BlitSurface(buffer, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	
	free(blockList);

	SDL_FreeSurface(buffer);

	return 0;
}

