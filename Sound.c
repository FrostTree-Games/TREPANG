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

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "Sound.h"



int init_sound()
{
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		perror("error initalizing SDL_mixer");
		return -1;
	}

	music = Mix_LoadMUS("bgm/danube.ogg");
	if (music == NULL)
	{
		perror("error loading danube.ogg");
		return -1;
	}
	titleMusic = Mix_LoadMUS("bgm/menumusic.ogg");
	if (music == NULL)
	{
		perror("error loading menumusic.ogg");
		return -1;
	}

	explode = Mix_LoadWAV("sfx/explode.wav");
	spit = Mix_LoadWAV("sfx/shoot.wav");

	if((explode==NULL) || (spit == NULL))
	{
		perror("error loading sound files");
		return -1;
	}

	return 0;
}

void playBGM()
{
	if (music != NULL)
	{
		Mix_PlayMusic(music, -1);
	}
}

void stopBGM()
{
	Mix_HaltMusic();
}

void playBGM2()
{
	if (titleMusic != NULL)
	{
		Mix_PlayMusic(titleMusic, -1);
	}
}

void stopBGM2()
{
	//
}

void deinit_sound()
{
	Mix_FreeMusic(music);
	Mix_FreeMusic(titleMusic);

	Mix_FreeChunk(explode);
	Mix_FreeChunk(spit);

	// close SDL_mixer
	Mix_CloseAudio();
}

int explode_sound()
{
	if( Mix_PlayChannel(-1, explode, 0) == -1)
	{
		return -1;
	}
	
	return 0;
}

int spit_sound()
{
	if( Mix_PlayChannel(-1, spit, 0) == -1)
	{
		return -1;
	}
	
	return 0;
}

