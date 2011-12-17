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

int loadAnims();

int freeAnims();
