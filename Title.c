/*Copyright (C) 2011 FrostTree Games
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Anim.h"
#include "Sound.h"
#include "Level.h"
#include "Title.h"

int titleScreen(SDL_Surface* screen)
{
	titleBuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, 0, 0, 0, 0);
	
	titleImg = IMG_Load("gfx/title0.png");
	titleImgBlink = IMG_Load("gfx/title1.png");
	bubbleBG = IMG_Load("gfx/bgroundbubbles.png");
	int flip = 0;
	int bubDelta = 0;
	
	Uint32 lastUpdateTime = SDL_GetTicks();

	int quit = 1;
	int spUp = 0;

	int returnVal = 0;

	while (quit == 1)
	{
		int i, j;

		// check for quit event
		while (SDL_PollEvent( &ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = 0;
				returnVal = -1;
			}
		}

		// keyboard input
		keystates = SDL_GetKeyState(NULL);
		if (keystates[SDLK_ESCAPE])
		{
			quit = 0;
			returnVal = -1;
		}
		if (keystates[SDLK_SPACE])
		{
			if (spUp == 0)
			{
				spUp = 1;
			}
		}
		else
		{
			if (spUp == 1)
			{
				quit = 0;
				returnVal = 0;
				spUp = 0;
			}
		}
		
		//update bubble distance
		bubDelta++;
		bubDelta = bubDelta % 16;

		//visuals
		SDL_FillRect(titleBuffer, NULL, SDL_MapRGB(titleBuffer->format, 146,254,253));
		
		//bubble loop
		for (i = 0; i < 21; i++)
		{
			for (j = 0; j < 21; j ++)
			{
				SDL_Rect bubR = {-16 + (i*16) + bubDelta, -16 + (j*16) + bubDelta, 0, 0};
				SDL_BlitSurface(bubbleBG, NULL, titleBuffer, &bubR);
			}
		}

		Uint32 currTime = SDL_GetTicks();
		if (currTime - lastUpdateTime > 1000)
		{
			if (flip == 0)
			{
				flip = 1;
			}
			else
			{
				flip = 0;
			}

			lastUpdateTime = currTime;
		}
		
		if (flip == 0)
		{
			SDL_BlitSurface(titleImg, NULL, titleBuffer, NULL);
		}
		else
		{
			SDL_BlitSurface(titleImgBlink, NULL, titleBuffer, NULL);
		}

		//SDL_BlitSurface(titleBuffer, NULL, screen, NULL);
		SDL_SoftStretch(titleBuffer, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	
	SDL_FreeSurface(titleBuffer);
	SDL_FreeSurface(titleImg);
	SDL_FreeSurface(titleImgBlink);

	return returnVal;
}

int nextLevelScreen(SDL_Surface* screen)
{
	titleBuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, 0, 0, 0, 0);
	levelCompleteImg = IMG_Load("gfx/levelcomplete.png");

	Uint32 startTime = SDL_GetTicks();
	
	int quit = 1;

	while (quit == 1)
	{
		// check for quit event
		while (SDL_PollEvent(&ev))
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

		if (SDL_GetTicks() - startTime > 1750)
		{
			quit = 0;
		}

		SDL_BlitSurface(levelCompleteImg, NULL, titleBuffer, NULL);
		//SDL_BlitSurface(titleBuffer, NULL, screen, NULL);
		SDL_SoftStretch(titleBuffer, NULL, screen, NULL);
		SDL_Flip(screen);
		
		SDL_Delay(20);

	}

	SDL_FreeSurface(levelCompleteImg);
	SDL_FreeSurface(titleBuffer);
	
	return 0;
}