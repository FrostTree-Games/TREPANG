#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

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

SDL_Surface* gui_HeartFull;
SDL_Surface* gui_HeartEmpty;
SDL_Surface* gui_minimap;

SDL_Surface* parallaxBG1;
SDL_Surface* parallaxBG2;

SDL_Surface* pBlockSurface;
SDL_Surface* betaExitSheet;

SDL_Surface* idleLeftSheet;
SDL_Surface* walkLeftSheet;
SDL_Surface* idleRightSheet;
SDL_Surface* walkRightSheet;
SDL_Surface* deathLeftSheet;
SDL_Surface* deathRightSheet;
SDL_Surface* shootSheetLeft;
SDL_Surface* shootSheetRight;

SDL_Surface* organAnimation1;
SDL_Surface* organAnimation2;
SDL_Surface* organAnimation3;
SDL_Surface* organDeathAnimation1;
SDL_Surface* organDeathAnimation2;
SDL_Surface* organDeathAnimation3;

SDL_Surface* starFishSheet;
SDL_Surface* starFishDeathSheet;

SDL_Surface* jellyFishSheet;
SDL_Surface* jellyFishDeathSheet;

SDL_Surface* squidSheetUp;
SDL_Surface* squidSheetUpDie;

TTF_Font* font;

int loadAnims();

int freeAnims();
