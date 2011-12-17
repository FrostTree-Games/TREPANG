#include <stdio.h>

#include "SDL/SDL.h"

// this data type will be used for the game's screen
SDL_Surface* screen;

int gameBackendSetup()
{
	// initalizes the SDL library
	if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
	{
		perror("Error on SDL_Init. Check your something");
		return -1;
	}
	
	// initalizes the screen pointer to the screen
	if ((screen = SDL_SetVideoMode( 320, 240, 32, SDL_SWSURFACE)) == NULL)
	{
		perror("Error on intialzing video memory.");
		return -1;
	}

	return 0;
}

int gameBackendClose()
{
	// frees the screen pointer and closes SDL
	SDL_Quit();

	return 0;
}

int main(int argc, char* argv[])
{
	// setup, exit if fail
	if (gameBackendSetup() == -1)
	{
		return -1;
	}

	SDL_Flip(screen);
	SDL_Delay(2000);

	// cleanup
	gameBackendClose();

	return 0;
}

