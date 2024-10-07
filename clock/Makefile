all: clock.exe

clock.exe : clock.o
	gcc -o clock.exe clock.o -L./raylib-4.2.0_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lwinmm

clock.o: clock.c
	gcc -I./raylib-4.2.0_win64_mingw-w64/include -c clock.c