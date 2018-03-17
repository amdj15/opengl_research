#my compiler
CC=clang++

#my program name
PRGNAME=booom

#library search directory
LIBDIR=-L/usr/local

#library names
#uses libSDL2.a, libGLEW.a
LIBNAME=-lGLEW -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

#includes for libraries
INCLUDES=-I/usr/local/include

#my compiler options
CFLAGS=-c -Wall -std=c++14

DIST=./bin

FILES=*.cpp

all: compile
	mkdir -p $(DIST)
	$(CC) $(LIBDIR) $(LIBNAME) -o $(DIST)/$(PRGNAME) *.o

compile:
	$(CC) $(CFLAGS) $(INCLUDES) src/$(FILES)

clean:
	rm -rf *.o $(DIST)
