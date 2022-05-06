all: main.o
	gcc main.o -o main.exe -lm
main.0: main.c stb_image.h
	 gcc -c main.c

