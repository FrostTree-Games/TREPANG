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

#include "Level.h"
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

	//SDL_Flip(screen);
	//SDL_Delay(2000);
	doLevel(screen);

	// cleanup
	gameBackendClose();

	return 0;
}

