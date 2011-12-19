all: Title.o Sound.o Level.o main.o
	gcc -g -Wall -o cwing.exe main.o Level.o Sound.o Title.o -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

main.o:
	gcc -g -Wall -c main.c

Level.o:
	gcc -g -Wall -c Level.c

Sound.o:
	gcc -g -Wall -c Sound.c

Title.o:
	gcc -g -Wall -c Title.c

clean:
	rm *.o cwing.exe

