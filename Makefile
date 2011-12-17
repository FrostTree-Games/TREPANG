all:
	gcc -Wall -o cwing.exe main.c -lmingw32 -lSDLmain -lSDL

clean:
	rm cwing.exe

