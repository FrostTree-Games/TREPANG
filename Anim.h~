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

SDL_Surface* idleLeftSheet;
SDL_Surface* walkLeftSheet;

int loadAnims();

int freeAnims();
