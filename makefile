all: main.o
	gcc main.o -o main -lm
main.0: main.c stb_image.h
	 gcc -c main.c

