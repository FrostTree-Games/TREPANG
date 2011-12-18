#include "SDL/SDL.h"

struct animation
{
	int loop; //true =1, false = 0
	SDL_Surface* fSheet;
	int animLength;
	int frameWidth;
	float frameSpeed; //number of ms per frame
};

struct animation* animationList;
int animationNum;

SDL_Surface* pCurrentSheet;
SDL_Surface* pBlockSurface;

SDL_Surface* idleLeftSheet;
SDL_Surface* walkLeftSheet;
SDL_Surface* idleRightSheet;
SDL_Surface* walkRightSheet;

SDL_Surface* organAnimation1;
SDL_Surface* organAnimation2;
SDL_Surface* organAnimation3;
SDL_Surface* organDeathAnimation1;
SDL_Surface* organDeathAnimation2;
SDL_Surface* organDeathAnimation3;

SDL_Surface* starFishSheet;

int loadAnims();

int freeAnims();
