#include "SDL/SDL.h"

Uint8* keystates;
SDL_Event ev;

Uint32 pLastTime;

int px;
int py;
float runSpeed;

struct block
{
	int x;
	int y;
};

struct block* blockList;
int blockCount;

SDL_Surface* buffer;

int doLevel(SDL_Surface* screen, int levelWidth, int levelHeight);


