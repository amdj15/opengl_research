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

DEFINE=GLEW_STATIC

DIST=./bin
FILES=*.cpp

all: compile
	mkdir -p $(DIST)
	cp -a resources/. $(DIST)/
	$(CC) $(LIBDIR) $(LIBNAME) -o $(DIST)/$(PRGNAME) *.o

compile:
	$(CC) $(CFLAGS) $(INCLUDES) -D $(DEFINE) src/$(FILES)

clean:
	rm -rf *.o $(DIST)
