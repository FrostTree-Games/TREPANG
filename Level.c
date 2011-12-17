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

void interpretLevel(int grid[][75])
{
	int i,j;

	blockCount = 0;
	blockList = malloc(100 * 75 * sizeof(struct block));

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 75; j++)
		{
			if (grid[i][j] == 1)
			{
				blockList[blockCount].x = i*16;
				blockList[blockCount].y = j*16;
				blockCount++;
			}
		}
	}
}

void generateMap(int grid[][75])
{
	int i,j;
	
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 75; j++)
		{
			if (i == 0 || j == 0 || i == 99 || j == 99)
			{
				grid[i][j] = 1;
			}
			else
			{
				grid[i][j] = rand() % 2;
			}
		}
	}
	
	int grid2[100][75];
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 75; j++)
		{
			grid2[i][j] = grid[i][j];
		}
	}

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 75; j++)
		{
			if (i == 0 || j == 0 || i == 99 || j == 99)
			{
				continue;
			}
			else
			{
				int count = 0;
				int q,l;

				for (q = -1; q < 2; q++)
				{
					for (l = -1; l < 2; l++)
					{
						if (grid2[i + q][j + l] == 1)
						{
							count++;
						}
					}
				}
				if (count < 5)
				{
					grid[i][j] = 0;
				}
				else if (count > 5)
				{
					grid[i][j] = 1;
				}
			}
		}
	}

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 75; j++)
		{
			grid2[i][j] = grid[i][j];
		}
	}
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 75; j++)
		{
			if (i == 0 || j == 0 || i == 99 || j == 99)
			{
				continue;
			}
			else
			{
				int count = 0;
				int q,l;

				for (q = -1; q < 2; q++)
				{
					for (l = -1; l < 2; l++)
					{
						if (grid2[i + q][j + l] == 1)
						{
							count++;
						}
					}
				}
				if (count < 5)
				{
					grid[i][j] = 0;
				}
				else if (count > 5)
				{
					grid[i][j] = 1;
				}
			}
		}
	}
	
	for (i = 0; i < 100; i++)
	{
		if (i < 75)
		{
			grid[0][i] = 1;
			grid[99][i] = 1;
		}
		grid[i][0] = 1;
		grid[i][74] = 1;
	}
}

int doLevel(SDL_Surface* screen, int levelWidth, int levelHeight)
{
	int quit = 1;

	int i,j;

	px = 48;
	py = 48;

	int grid[100][75];

	generateMap(grid);
	interpretLevel(grid);

	/*blockCount = 5;
	blockList = malloc(blockCount * sizeof(struct block));
	for (i = 0; i < blockCount; i++)
	{
		blockList[i].x = i * 32;
		blockList[i].y = 64;
	}                      */

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

