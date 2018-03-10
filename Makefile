#my compiler
CC=clang++

#my program name
PRGNAME=booom

#library search directory
LIBDIR=-L/usr/local

#library names
#uses libSDL2.a, libGLEW.a
LIBNAME=-lGLEW -framework OpenGL\
				-lsfml-graphics -lsfml-window -lsfml-system

#includes for libraries
INCLUDES=-I/usr/local/include

#my compiler options
CFLAGS=-c -Wall

all: main.o
	$(CC) $(LIBDIR) $(LIBNAME) -o $(PRGNAME) main.o

#main.cpp is the dependency of main.o
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) main.cpp

clean:
	rm -rf *o booom
