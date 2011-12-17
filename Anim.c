#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Anim.h"

/* animationList[0] - cubumber idling left animation
 * animationList[1] - cubumber idling right animation
 * animationList[2] - cucumber moving left animation
 * animationList[3] - cucumber moving right animation
 */

int loadAnims()
{
	SDL_Surface* loadedImage = NULL;

	animationNum = 1;
	animationList = malloc(1 * sizeof(struct animation));
	
	loadedImage =  IMG_Load("gfx/cucumberidleLeft.png");
	if (loadedImage != NULL)
	{
		animationList[0].fSheet = SDL_DisplayFormat(loadedImage);
		animationList[0].frameWidth = 16;
		animationList[0].animLength = (animationList[0].fSheet)->w / animationList[0].frameWidth;
		animationList[0].frameSpeed = 83.3f;
		SDL_FreeSurface(loadedImage);
	}
	else
	{
		perror("ERROR LOADING cucumberidleLeft.png");
		return -1;
	}

	return 0;
}

int freeAnims()
{
	int i;
	for (i = 0; i < animationNum; i++)
	{
		if (animationList[i].fSheet != NULL)
		{
			SDL_FreeSurface(animationList[i].fSheet);
		}
	}
	free(animationList);
	return 0;
}