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
#include "Level.h"
#include "Anim.h"

#define x_length 100
#define y_length 75

struct Point{
	int x;
	int y;
};

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

	if (currTime - pLastUpdate > 83)
	{
		pLastUpdate = currTime;
		pFrame++;
		pFrame = pFrame % ((pCurrentSheet->w)/16);
	}

	float pXSpeed = 0.0f;
	float pYSpeed = 0.0f;
	if (keystates[SDLK_RIGHT])
	{
		if(rDown == 0)
		{
			pCurrentSheet = walkRightSheet;
			pFrame = 0;
			rDown = 1;
			pDirection = 1;
		}
		pXSpeed = runSpeed;
	}
	else if (keystates[SDLK_LEFT])
	{
		if (lDown == 0)
		{
			pCurrentSheet = walkLeftSheet;
			pFrame = 0;
			lDown = 1;
			pDirection = 0;
		}
		pXSpeed = -runSpeed;
	}
	else
	{
		if (lDown == 1)
		{
			pCurrentSheet = idleLeftSheet;
			pFrame = 0;
			lDown = 0;
		}
		if( rDown == 1 )
		{
			pCurrentSheet = idleRightSheet;
			pFrame = 0;
			rDown = 0;
		}
		pXSpeed = 0.0f;
	}

	if (keystates[SDLK_DOWN])
	{
		pYSpeed = runSpeed;
		if (dDown == 0)
		{
			if (pDirection == 0)
			{
				pCurrentSheet = walkLeftSheet;
				dDown = 1;
			}
			else
			{
				pCurrentSheet = walkRightSheet;
				dDown = 1;
			}
		}
	}
	else if (keystates[SDLK_UP])
	{
		pYSpeed = -runSpeed;
		if (uDown == 0)
		{
			if (pDirection == 0)
			{
				pCurrentSheet = walkLeftSheet;
				uDown = 1;
			}
			else
			{
				pCurrentSheet = walkRightSheet;
				uDown = 1;
			}
		}
	}
	else
	{
		if (uDown == 1 || dDown == 1)
		{
			if (pDirection == 0)
			{
				pCurrentSheet = idleLeftSheet;
				uDown = 0;
				dDown = 0;
			}
			else
			{
				pCurrentSheet = idleRightSheet;
				uDown = 0;
				dDown = 0;
			}
			pFrame = 0;
		}
		pYSpeed = 0.0f;
	}
	
	if (keystates[SDLK_z])
	{
		if (organOnScreen == 0)
		{
			time_t seconds;
			time(&seconds);
			srand((unsigned int) seconds);

			switch(rand() % 3)
			{
				case 0:
				organCurrentSheet = organAnimation1;
				break;
				case 1:
				organCurrentSheet = organAnimation2;
				break;
				case 2:
				organCurrentSheet = organAnimation3;
				break;
			}
			organOnScreen = 1;
			organBirthTime = currTime;
			organLastTime = organBirthTime;
			organFrame = 0;
			organX = px;
			organY = py;
			if (pXSpeed != 0.0f)
			{
				organXSpeed = pXSpeed*1.5;
				organYSpeed = pYSpeed*1.5;
			}
			else
			{
				if (pDirection == 0)
				{
					organXSpeed = -runSpeed*1.5;
					organYSpeed = 0.0f;
				}
				else
				{
					organXSpeed = runSpeed*1.5;
					organYSpeed = 0.0f;
				}
			}
		}
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

void updateOrgan(Uint32 currTime)
{
	int i;

	// return if not updating
	if (organOnScreen == 0)
	{
		return;
	}

	Uint32 tDiff = currTime - organLastTime;
	
	if (currTime - organLastUpdate > 83)
	{
		organLastUpdate = currTime;
		organFrame++;
		if (organBlowingUp == 1 && organFrame >= ((organCurrentSheet->w)/16))
		{
			organBlowingUp = 0;
			organOnScreen = 0;
			return;
		}
		else
		{
			organFrame = organFrame % ((organCurrentSheet->w)/16);
		}
	}

	organX += (int)((organXSpeed/1000.0)*tDiff);
	organY += (int)((organYSpeed/1000.0)*tDiff);
	
	for (i = 0; i < blockCount; i++)
	{
		if (hitTest(organX, organY, 16, 16, blockList[i].x, blockList[i].y, 16, 16))
		{
			//organOnScreen = 0;
			if (organBlowingUp == 0)
			{
				organBlowingUp = 1;
				organXSpeed = 0.0f;
				organYSpeed = 0.0f;
				
				if (organCurrentSheet == organAnimation1)
				{
					organCurrentSheet = organDeathAnimation1;
				}
				else if (organCurrentSheet == organAnimation2)
				{
					organCurrentSheet = organDeathAnimation2;
				}
				else if(organCurrentSheet == organAnimation3)
				{
					organCurrentSheet = organDeathAnimation3;
				}
				
				organFrame = 0;
			}
		}
	}
	
	// if the elapsed time the organ has been alive is greater than some seconds,
	// then set the organ to not exist
	if (currTime - organBirthTime > 650 && organBlowingUp == 0)
	{
		//organOnScreen = 0;
		if (organBlowingUp == 0)
		{
			organBlowingUp = 1;
			organXSpeed = 0.0f;
			organYSpeed = 0.0f;
			
			if (organCurrentSheet == organAnimation1)
			{
				organCurrentSheet = organDeathAnimation1;
			}
			else if (organCurrentSheet == organAnimation2)
			{
				organCurrentSheet = organDeathAnimation2;
			}
			else if(organCurrentSheet == organAnimation3)
			{
				organCurrentSheet = organDeathAnimation3;
			}
			
			organFrame = 0;
		}
	}

	organLastTime = currTime;
}

void updateEnemy(struct enemy* en, Uint32 currTime)
{
	switch (en->ai)
	{
		case CHILL:
		if (currTime - en->eLastUpdate > 83)
		{
			en->eLastUpdate = currTime;
			en->eFrame++;
			en->eFrame = en->eFrame % ((starFishSheet->w)/16);
		}
		break;
		case WIGGLE:
		break;
		case CHASE:
		break;
	}
}

void updateEnemyList(Uint32 currTime)
{
	int i = 0;

	while (i < enemyCount)
	{
		updateEnemy(&enemyList[i], currTime);
		i++;
	}
}

void drawVisuals()
{
	int i;

	SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format,50,50,235));

	//SDL_Rect r = {(Sint16)(buffer->w)/2, (Sint16)(buffer->h)/2, 16, 16};
	//SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 255, 255));
	SDL_Rect rFrom = {(Sint16)(16*pFrame), 0, 16, 16};
	SDL_Rect rTo = {(Sint16)(buffer->w)/2, (Sint16)(buffer->h)/2, 0, 0};
	SDL_BlitSurface(pCurrentSheet, &rFrom, buffer, &rTo);

	//draw organ
	if( organOnScreen == 1)
	{
		//SDL_Rect organRect = {(Sint16)(organX - px + ((buffer->w)/2)), (Sint16)(organY - py + ((buffer->h)/2)), 16, 16};
		//SDL_FillRect(buffer, &organRect, SDL_MapRGB(buffer->format, 155,155,155));
		SDL_Rect organRectFrom = {(Sint16)(16*organFrame), 0, 16, 16};
		SDL_Rect organRectTo = {(Sint16)(organX - px + ((buffer->w)/2)), (Sint16)(organY - py + ((buffer->h)/2)), 0, 0};
		SDL_BlitSurface(organCurrentSheet, &organRectFrom, buffer, &organRectTo);
	}

	for (i = 0; i < blockCount; i++)
	{
		if (blockList[i].x > px - (buffer->w)/2 - 16 && blockList[i].x < px + (buffer->w)/2)
		{
			if (blockList[i].y > py - (buffer->h)/2 - 16 && blockList[i].y < py + (buffer->h)/2)
			{
				SDL_Rect r = {(Sint16)(blockList[i].x - px + ((buffer->w)/2)), (Sint16)(blockList[i].y - py + ((buffer->h)/2)), 16, 16};
				SDL_BlitSurface( pBlockSurface, NULL, buffer, &r);
				//SDL_FillRect(buffer, &r, SDL_MapRGB(buffer->format, 0, 0, 0));
			}
		}
	}
	
	for (i = 0; i < enemyCount; i++)
	{
		if (enemyList[i].dead == 1)
		{
			continue;
		}

		if (enemyList[i].ex > px - (buffer->w)/2 - 16 && enemyList[i].ex < px + (buffer->w)/2)
		{
			if (enemyList[i].ey > py - (buffer->h)/2 - 16 && enemyList[i].ey < py + (buffer->h)/2)
			{
				SDL_Rect rFrom = {(Sint16)(16*enemyList[i].eFrame), 0, 16, 16};
				SDL_Rect rTo = {(Sint16)(enemyList[i].ex - px + ((buffer->w)/2)), (Sint16)(enemyList[i].ey - py + ((buffer->h)/2)), 0, 0};
				switch (enemyList[i].ai)
				{
					case CHILL:
					SDL_BlitSurface(starFishSheet , &rFrom, buffer, &rTo);
					break;
					default:
					break;
				}
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
	
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	
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
				grid[i][j] = rand()  % 2;
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

void print_dijkstra( int d_grid[][75] )
{
	int i;
	int j;
	
	for( i = 0; i < x_length; i++ )
	{
		for( j = 0; j < y_length; j++ )
		{
			if( d_grid[j][i] < 100 )
			{
				printf(" ");
			}
			if( d_grid[j][i] < 10 )
			{
				printf(" ");
			}
			
			printf(" %d", d_grid[j][i]);
		}
		printf("\n");
	}
}

void locating_start_end( int grid[][75] )
{
	int dijkstra_grid[100][75];
	int visited[100][75];
	int i = 0;
	int j = 0;
	
	struct Point queue[100*75];
	int queue_position = 0;
	int queue_end = 0;
	
	
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);

	for( i = 0; i< x_length; i++ )
	{
		for( j = 0; j < y_length; j++ )
		{
			dijkstra_grid[i][j] = 999;
			visited[i][j] = 0;
		}
	}
	
	int x_start = rand()%100;
	int y_start = rand()%75;
	
	while( grid[x_start][y_start] == 1 )
	{
		x_start = rand()%100;
		y_start = rand()%75;
	}

	px = (x_start)*16;
	py = (y_start)*16;
	
	queue[queue_end].x = x_start;
	queue[queue_end].y = y_start;
	
	grid[x_start][y_start] = 2; //sets the start position
	dijkstra_grid[x_start][y_start] = 0; //set start as 0
	
//	printf("point.x = %d\n", point[num_point].x);
//	printf("point.y = %d\n", point[num_point].y);
	
	//	printf("point.x = %d\n", queue[queue_position].x);
//	printf("point.y = %d\n", queue[queue_position].y);
	
	queue_end++;
	
	int x_final= rand()%100;
	int y_final = rand()%75;
	
	while( grid[x_final][y_final] == 1 )
	{
		x_final = rand()%100;
		y_final = rand()%75;
	}
	
	grid[x_final][y_final] = 3;
	
	int current_x;
	int current_y;
	
//	printf("queue_position: %d\n", queue_position);
	while( queue_end - queue_position > 0 )
	{
	//	printf("qEnd:%d qPos:%d\n", queue_end, queue_position);
		int i;
		int j;
		//int current_source = queue_position;
		current_x = queue[queue_position].x;
		current_y = queue[queue_position].y;
		queue_position++;

		if (visited[current_x][current_y] == 1)
		{
			continue;
		}
		
		visited[current_x][current_y] = 1;
		//printf("current.x = %d\n", current_x);
		//printf("current.y = %d\n", current_y);
		
		for( i = -1; i < 2; i++ )
		{
			for( j = -1; j < 2; j++ )
			{
				if ( i == -1 && j != 0 )
				{
					continue;
				}
				
				else if( i == 1 && j != 0 )
				{
					continue;
				}
				
				//if( grid[current_x+i][current_y+j] == 0 && dijkstra_grid[current_x+i][current_y+j] == 999 )
				if( grid[current_x+i][current_y+j] == 0 && visited[current_x+i][current_y+j] == 0 )
				{
					queue[queue_end].x = current_x+i;
					queue[queue_end].y = current_y+j;
				/*	printf("current.x = %d\n", current_x);
					printf("current.y = %d\n", current_y);
					printf("current.x+i = %d\n", current_x+i);
					printf("current.y+j = %d\n", current_y+j);
					
					printf("dijkstra_grid[current_x][current_y] %d\n", dijkstra_grid[current_x][current_y]);
					printf("dijkstra_grid[current_x+i][current_y+j] %d\n", dijkstra_grid[current_x+i][current_y+j]);*/
					
					queue_end++;
					
					//printf("queue_position in forloop: %d\n", queue_position);
					if (dijkstra_grid[current_x+i][current_y+j] > dijkstra_grid[current_x][current_y] + 1)
					{
						dijkstra_grid[current_x+i][current_y+j] = dijkstra_grid[current_x][current_y] + 1;
//printf("new current.x+i = %d\n", current_x+i);
	//					printf("new current.y+j = %d\n", current_y+j);
					}
				}
			}
		}
	//	printf("\n");
	}
	int l = 0;

	while (l < enemyCount)
	{
		int potX = (rand() % 98) + 1;
		int potY = (rand() % 73) + 1;
		if (grid[potX][potY] == 1)
		{
			l--;
			continue;
		}
		enemyList[l].ex = potX*16;
		enemyList[l].ey = potY*16;
		enemyList[l].ai = CHILL;
		enemyList[l].eLastUpdate = SDL_GetTicks();
		enemyList[l].eFrame = 0;
                enemyList[l].dead = 0;
		
		l++;
	}
	//print_dijkstra( dijkstra_grid );
}


int doLevel(SDL_Surface* screen, int levelWidth, int levelHeight)
{
	int quit = 1;

	//printf("one\n");

	int grid[100][75];
	
	enemyCount = 50;

	generateMap(grid);
	locating_start_end(grid);
	interpretLevel(grid);
	
	//printf("two\n");

	pLastTime = SDL_GetTicks();

	buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 32, 0, 0, 0, 0);

	pBlockSurface = IMG_Load("gfx/beachtileLEGO.png");

	idleLeftSheet = IMG_Load("gfx/cucumberidleLeft.png");
	walkLeftSheet = IMG_Load("gfx/cucumberWalkLeft.png");
	idleRightSheet = IMG_Load("gfx/cucumberidleRight.png");
	walkRightSheet = IMG_Load("gfx/cucumberWalkRight.png");
	
	organAnimation1 = IMG_Load("gfx/cucumberGib1.png");
	organAnimation2 = IMG_Load("gfx/cucumberGib2.png");
	organAnimation3 = IMG_Load("gfx/cucumberGib3.png");
	organDeathAnimation1 = IMG_Load("gfx/cucumberGib1Die.png");
	organDeathAnimation2 = IMG_Load("gfx/cucumberGib2Die.png");
	organDeathAnimation3 = IMG_Load("gfx/cucumberGib3Die.png");
	
	starFishSheet = IMG_Load("gfx/starfishIdle.png");

	organOnScreen = 0;
	organX = 0;
	organY = 0;
	organXSpeed = 0.0f;
	organYSpeed = 0.0f;
	organLastTime = 0;;
	organFrame = 0;
	organLastUpdate = SDL_GetTicks();
	organCurrentSheet = organAnimation1;

	runSpeed = 100.0f;
	pFrame = 0;
	pLastUpdate = pLastTime;
	lDown = 0;
	rDown = 0;
	uDown = 0;
	dDown = 0;
	pCurrentSheet = idleLeftSheet;
	pDirection = 0;

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
		updateOrgan(currTicks);
		updateEnemyList(currTicks);

		drawVisuals();

		SDL_BlitSurface(buffer, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(20);
	}

	free(blockList);

	SDL_FreeSurface(buffer);

	return 0;
}
