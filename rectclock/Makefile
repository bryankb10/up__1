all: rectangleclock.exe

rectangleclock.exe : rectangleclock.o
	gcc -o rectangleclock.exe rectangleclock.o -L../raylib-4.2.0_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lwinmm

rectangleclock.o: rectangleclock.c
	gcc -I../raylib-4.2.0_win64_mingw-w64/include -c rectangleclock.c