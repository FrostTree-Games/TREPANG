#include "SDL/SDL.h"

struct animation
{
	int loop; //true =1, false = 0
	SDL_Surface* fSheet;
	int animLength;
	int frameWidth;
	int frameHeight;
	float frameSpeed; //number of ms per frame
};

int loadAnims();

int freeAnims();
