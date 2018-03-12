#my compiler
CC=clang++

#my program name
PRGNAME=booom

#library search directory
LIBDIR=-L/usr/local

#library names
#uses libSDL2.a, libGLEW.a
LIBNAME=-lGLEW -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

#-lsfml-graphics -lsfml-window -lsfml-system

#includes for libraries
INCLUDES=-I/usr/local/include

#my compiler options
CFLAGS=-c -Wall -std=c++14

all: main.o
	$(CC) $(LIBDIR) $(LIBNAME) -o $(PRGNAME) main.o

#main.cpp is the dependency of main.o
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) main.cpp

clean:
	rm -rf *o booom
