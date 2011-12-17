all: Anim.o Level.o main.o
	gcc -g -Wall -o cwing.exe main.o Level.o Anim.o -lmingw32 -lSDLmain -lSDL -lSDL_image

main.o:
	gcc -g -Wall -c main.c

Level.o:
	gcc -g -Wall -c Level.c

Anim.o:
	gcc -g -Wall -c Anim.c

clean:
	rm *.o cwing.exe

