all: Sound.o Level.o main.o
	gcc -g -Wall -o cwing.exe main.o Level.o Sound.o -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer

main.o:
	gcc -g -Wall -c main.c

Level.o:
	gcc -g -Wall -c Level.c

Sound.o:
	gcc -g -Wall -c Sound.c

clean:
	rm *.o cwing.exe

